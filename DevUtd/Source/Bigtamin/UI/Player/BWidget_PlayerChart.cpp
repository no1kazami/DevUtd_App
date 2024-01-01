#include "BWidget_PlayerChart.h"
#include "UI/Equip/BWidget_EquipFilterItem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Bigtamin.h"

void UBWidget_PlayerChart::Init()
{
	Super::Init();

	ButtonDelegate_Clicked( this, C_Btn_Day1, &UBWidget_PlayerChart::_OnClick_Day1 );
	ButtonDelegate_Clicked( this, C_Btn_Day2, &UBWidget_PlayerChart::_OnClick_Day2 );
	ButtonDelegate_Clicked( this, C_Btn_Day3, &UBWidget_PlayerChart::_OnClick_Day3 );
	ButtonDelegate_Clicked( this, C_Btn_Day4, &UBWidget_PlayerChart::_OnClick_Day4 );
	ButtonDelegate_Clicked( this, C_Btn_Day5, &UBWidget_PlayerChart::_OnClick_Day5 );
	ButtonDelegate_Clicked( this, C_Btn_Day6, &UBWidget_PlayerChart::_OnClick_Day6 );
	ButtonDelegate_Clicked( this, C_Btn_Day7, &UBWidget_PlayerChart::_OnClick_Day7 );

	ButtonDelegate_Clicked( this, C_Btn_Week1, &UBWidget_PlayerChart::_OnClick_Week1 );
	ButtonDelegate_Clicked( this, C_Btn_Week2, &UBWidget_PlayerChart::_OnClick_Week2 );
	ButtonDelegate_Clicked( this, C_Btn_Week3, &UBWidget_PlayerChart::_OnClick_Week3 );
	ButtonDelegate_Clicked( this, C_Btn_Week4, &UBWidget_PlayerChart::_OnClick_Week4 );

	ButtonDelegate_Clicked( this, C_Btn_Month1, &UBWidget_PlayerChart::_OnClick_Month1 );
	ButtonDelegate_Clicked( this, C_Btn_Month2, &UBWidget_PlayerChart::_OnClick_Month2 );
	ButtonDelegate_Clicked( this, C_Btn_Month3, &UBWidget_PlayerChart::_OnClick_Month3 );
	ButtonDelegate_Clicked( this, C_Btn_Month4, &UBWidget_PlayerChart::_OnClick_Month4 );
	ButtonDelegate_Clicked( this, C_Btn_Month5, &UBWidget_PlayerChart::_OnClick_Month5 );
	ButtonDelegate_Clicked( this, C_Btn_Month6, &UBWidget_PlayerChart::_OnClick_Month6 );

	BP_Day_UMG->Init();
	BP_Day_UMG->SetDetailInfoFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_DAY, 40 );
	if( BP_Day_UMG->OnClickDetailInfoFilter.IsBoundToObject( this ) == false )
	{
		BP_Day_UMG->OnClickDetailInfoFilter.AddUObject( this, &UBWidget_PlayerChart::OnClickPeriodFilter );
	}
	BP_Week_UMG->Init();
	BP_Week_UMG->SetDetailInfoFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_WEEK, 41 );
	if( BP_Week_UMG->OnClickDetailInfoFilter.IsBoundToObject( this ) == false )
	{
		BP_Week_UMG->OnClickDetailInfoFilter.AddUObject( this, &UBWidget_PlayerChart::OnClickPeriodFilter );
	}
	BP_Month_UMG->Init();
	BP_Month_UMG->SetDetailInfoFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_MONTH, 42 );
	if( BP_Month_UMG->OnClickDetailInfoFilter.IsBoundToObject( this ) == false )
	{
		BP_Month_UMG->OnClickDetailInfoFilter.AddUObject( this, &UBWidget_PlayerChart::OnClickPeriodFilter );
	}

	OnClickPeriodFilter( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_DAY, true );

	_PlayerName.Empty();
	_CalcChartBaseData();
}

void UBWidget_PlayerChart::OnClose()
{
	Super::OnClose();
}


int32 UBWidget_PlayerChart::NativePaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const
{
	FPaintContext Context( AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled );
	_DrawChartDay( Context );

	return Super::NativePaint( Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled );
}

void UBWidget_PlayerChart::SetPlayerData( E_SORT_TYPE type, const FString PlayerName )
{
	_ChartType = type;
	_PlayerName = PlayerName;

	if( _ChartType == E_SORT_TYPE::E_SORT_TYPE_GOAL )
	{
		C_Txt_Title->SetText( GET_BTEXT( 49 ) );
	}
	else if( _ChartType == E_SORT_TYPE::E_SORT_TYPE_ASSIST )
	{
		C_Txt_Title->SetText( GET_BTEXT( 50 ) );
	}
	
	// 최근 7경기
	_DayMatchData.Empty();
	const FST_PLAYER_DATA* playerData = UFBM_SaveGame::Get().GetPlayerData_DB_ByName( PlayerName );
	if( playerData )
	{
		if ( _ChartType == E_SORT_TYPE::E_SORT_TYPE_GOAL)
		{
			for( auto& Elem : playerData->RecentDayGoalNum )
			{
				_DayMatchData.Add( FST_PLAYER_CHART_INFO_DATA( Elem.Key, Elem.Value, 0 ) );
			}
		}
		else if( _ChartType == E_SORT_TYPE::E_SORT_TYPE_ASSIST )
		{
			for( auto& Elem : playerData->RecentDayAssistNum )
			{
				_DayMatchData.Add( FST_PLAYER_CHART_INFO_DATA( Elem.Key, 0, Elem.Value ) );
			}
		}
	}

	// 최근 4주
	_WeekMatchData.Empty();
	if( playerData )
	{
		if( _ChartType == E_SORT_TYPE::E_SORT_TYPE_GOAL )
		{
			for( auto& Elem : playerData->RecentWeekGoalNum )
			{
				_WeekMatchData.Add( FST_PLAYER_CHART_INFO_DATA( Elem.Key, Elem.Value, 0 ) );
			}
		}
		else if( _ChartType == E_SORT_TYPE::E_SORT_TYPE_ASSIST )
		{
			for( auto& Elem : playerData->RecentWeekAssistNum )
			{
				_WeekMatchData.Add( FST_PLAYER_CHART_INFO_DATA( Elem.Key, 0, Elem.Value ) );
			}
		}
	}

	// 최근 6개월
	_MonthMatchData.Empty();
	if( playerData )
	{
		if( _ChartType == E_SORT_TYPE::E_SORT_TYPE_GOAL )
		{
			for( auto& Elem : playerData->RecentMonthGoalNum )
			{
				_MonthMatchData.Add( FST_PLAYER_CHART_INFO_DATA( Elem.Key, Elem.Value, 0 ) );
			}
		}
		else if( _ChartType == E_SORT_TYPE::E_SORT_TYPE_ASSIST )
		{
			for( auto& Elem : playerData->RecentMonthAssistNum )
			{
				_MonthMatchData.Add( FST_PLAYER_CHART_INFO_DATA( Elem.Key, 0, Elem.Value ) );
			}
		}
	}

	_TestData();
}

void UBWidget_PlayerChart::_CalcCurPriceTextPosition( UBButton* btn, int32 dataIndex )
{
	if( btn != nullptr )
	{
		UCanvasPanelSlot* btnSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot( btn );
		if( btnSlot != nullptr )
		{
			FVector2D pixelPosition;
			FVector2D viewportPosition;
			FGeometry geo = UWidgetLayoutLibrary::GetViewportWidgetGeometry( this->GetWorld() );
			USlateBlueprintLibrary::LocalToViewport( this->GetWorld(), geo, btnSlot->GetPosition(), pixelPosition, viewportPosition );

			UCanvasPanelSlot* dotOverSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot( C_Img_DotOver );
			if( dotOverSlot != nullptr )
			{
				C_Img_DotOver->SetVisibility( ESlateVisibility::Visible );
				dotOverSlot->SetPosition( viewportPosition );
			}

			UCanvasPanelSlot* curTxtSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot( C_Txt_ClickPrice );
			if( curTxtSlot != nullptr )
			{
				viewportPosition.Y -= 150.f;
				curTxtSlot->SetPosition( viewportPosition );

				uint32 priceData;
				switch( _PeriodFilterType )
				{
				case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_DAY:
					priceData = _ChartType == E_SORT_TYPE::E_SORT_TYPE_ASSIST ? _DayMatchData[dataIndex].Assist : _DayMatchData[dataIndex].Goal;
					break;
				case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_WEEK:
					priceData = _ChartType == E_SORT_TYPE::E_SORT_TYPE_ASSIST ? _WeekMatchData[dataIndex].Assist : _WeekMatchData[dataIndex].Goal;
					break;
				case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_MONTH:
					priceData = _ChartType == E_SORT_TYPE::E_SORT_TYPE_ASSIST ? _MonthMatchData[dataIndex].Assist : _MonthMatchData[dataIndex].Goal;
					break;
				default:
					priceData = 0;
					break;
				}

				if ( _ChartType == E_SORT_TYPE::E_SORT_TYPE_ASSIST )
				{
					C_Txt_ClickPrice->SetText( FText::Format( GET_BTEXT( 23 ), FText::AsNumber( priceData ) ) );
				}
				else
				{
					C_Txt_ClickPrice->SetText( FText::Format( GET_BTEXT( 22 ), FText::AsNumber( priceData ) ) );
				}
		
				C_Txt_ClickPrice->SetVisibility( ESlateVisibility::Visible );
			}
		}
	}
}

void UBWidget_PlayerChart::_TestData()
{
#if PLATFORM_WINDOWS
	//////////////////////////////////////////////
	// Test용 임시 데이터
	_DayPriceData.Empty();
	_DayPriceData.Add( FST_LOW_PRICE_INFO_DATA( "200513_HMall", 257000 ) );
	_DayPriceData.Add( FST_LOW_PRICE_INFO_DATA( "05.14", E_CRAWLING_WEBPAGE::HMALL, 237000 ) );
	_DayPriceData.Add( FST_LOW_PRICE_INFO_DATA( "05.15", E_CRAWLING_WEBPAGE::HMALL, 227000 ) );
	_DayPriceData.Add( FST_LOW_PRICE_INFO_DATA( "05.16", E_CRAWLING_WEBPAGE::HMALL, 297000 ) );
	_DayPriceData.Add( FST_LOW_PRICE_INFO_DATA( "05.17", E_CRAWLING_WEBPAGE::HMALL, 259000 ) );
	_DayPriceData.Add( FST_LOW_PRICE_INFO_DATA( "05.18", E_CRAWLING_WEBPAGE::HMALL, 240000 ) );
	_DayPriceData.Add( FST_LOW_PRICE_INFO_DATA( "05.19", E_CRAWLING_WEBPAGE::HMALL, 307000 ) );

	_WeekPriceData.Empty();
	_WeekPriceData.Add( FST_LOW_PRICE_INFO_DATA( "202019_HMall", 237000 ) );
	_WeekPriceData.Add( FST_LOW_PRICE_INFO_DATA( "202020_HMall", 237000 ) );
	_WeekPriceData.Add( FST_LOW_PRICE_INFO_DATA( "202021_HMall", 237000 ) );
	_WeekPriceData.Add( FST_LOW_PRICE_INFO_DATA( "202022_HMall", 237000 ) );

	_MonthPriceData.Empty();
	_MonthPriceData.Add( FST_LOW_PRICE_INFO_DATA( "201912_HMall", 237000 ) );
	_MonthPriceData.Add( FST_LOW_PRICE_INFO_DATA( "202001_HMall", 247000 ) );
	_MonthPriceData.Add( FST_LOW_PRICE_INFO_DATA( "202002_HMall", 257000 ) );
	_MonthPriceData.Add( FST_LOW_PRICE_INFO_DATA( "202002_HMall", 297000 ) );
	_MonthPriceData.Add( FST_LOW_PRICE_INFO_DATA( "202004_HMall", 277000 ) );
	_MonthPriceData.Add( FST_LOW_PRICE_INFO_DATA( "202005_HMall", 307000 ) );

	_DayMatchData.Empty();
	_DayMatchData.Add( FST_PLAYER_CHART_INFO_DATA( "20221202", 1, 1 ) );
	_DayMatchData.Add( FST_PLAYER_CHART_INFO_DATA( "20221203", 2, 3 ) );
	_DayMatchData.Add( FST_PLAYER_CHART_INFO_DATA( "20221204", 0, 3 ) );
	_DayMatchData.Add( FST_PLAYER_CHART_INFO_DATA( "20221205", 5, 0 ) );
	_DayMatchData.Add( FST_PLAYER_CHART_INFO_DATA( "20221206", 2, 4 ) );
	_DayMatchData.Add( FST_PLAYER_CHART_INFO_DATA( "20221207", 2, 1 ) );
	_DayMatchData.Add( FST_PLAYER_CHART_INFO_DATA( "20221208", 6, 2 ) );

	_MonthMatchData.Empty();
	_MonthMatchData.Add( FST_PLAYER_CHART_INFO_DATA( "202212", 1, 1 ) );
	_MonthMatchData.Add( FST_PLAYER_CHART_INFO_DATA( "202211", 2, 3 ) );
	_MonthMatchData.Add( FST_PLAYER_CHART_INFO_DATA( "202210", 0, 3 ) );
	_MonthMatchData.Add( FST_PLAYER_CHART_INFO_DATA( "202209", 5, 0 ) );
	_MonthMatchData.Add( FST_PLAYER_CHART_INFO_DATA( "202208", 2, 4 ) );
	_MonthMatchData.Add( FST_PLAYER_CHART_INFO_DATA( "202207", 2, 1 ) );
	/////////////////////////////////////////////////
#endif
}

void UBWidget_PlayerChart::_OnClick_Day1()
{
	if( _DayMatchData.IsValidIndex( 0 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Day1, 0 );
	}
}

void UBWidget_PlayerChart::_OnClick_Day2()
{
	if( _DayMatchData.IsValidIndex( 1 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Day2, 1 );
	}
}

void UBWidget_PlayerChart::_OnClick_Day3()
{
	if( _DayMatchData.IsValidIndex( 2 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Day3, 2 );
	}
}

void UBWidget_PlayerChart::_OnClick_Day4()
{
	if( _DayMatchData.IsValidIndex( 3 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Day4, 3 );
	}
}

void UBWidget_PlayerChart::_OnClick_Day5()
{
	if( _DayMatchData.IsValidIndex( 4 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Day5, 4 );
	}
}

void UBWidget_PlayerChart::_OnClick_Day6()
{
	if( _DayMatchData.IsValidIndex( 5 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Day6, 5 );
	}
}

void UBWidget_PlayerChart::_OnClick_Day7()
{
	if( _DayMatchData.IsValidIndex( 6 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Day7, 6 );
	}
}

void UBWidget_PlayerChart::_OnClick_Week1()
{
	if( _WeekMatchData.IsValidIndex( 0 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Week1, 0 );
	}
}

void UBWidget_PlayerChart::_OnClick_Week2()
{
	if( _WeekMatchData.IsValidIndex( 1 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Week2, 1 );
	}
}

void UBWidget_PlayerChart::_OnClick_Week3()
{
	if( _WeekMatchData.IsValidIndex( 2 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Week3, 2 );
	}
}

void UBWidget_PlayerChart::_OnClick_Week4()
{
	if( _WeekMatchData.IsValidIndex( 3 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Week4, 3 );
	}
}

void UBWidget_PlayerChart::_OnClick_Month1()
{
	if( _MonthMatchData.IsValidIndex( 0 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Month1, 0 );
	}
}

void UBWidget_PlayerChart::_OnClick_Month2()
{
	if( _MonthMatchData.IsValidIndex( 1 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Month2, 1 );
	}
}

void UBWidget_PlayerChart::_OnClick_Month3()
{
	if( _MonthMatchData.IsValidIndex( 2 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Month3, 2 );
	}
}

void UBWidget_PlayerChart::_OnClick_Month4()
{
	if( _MonthMatchData.IsValidIndex( 3 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Month4, 3 );
	}
}

void UBWidget_PlayerChart::_OnClick_Month5()
{
	if( _MonthMatchData.IsValidIndex( 4 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Month5, 4 );
	}
}

void UBWidget_PlayerChart::_OnClick_Month6()
{
	if( _MonthMatchData.IsValidIndex( 5 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Month6, 5 );
	}
}

void UBWidget_PlayerChart::_CalcChartBaseData()
{
	// 차트 최소, 최대 높이 구하기
	UCanvasPanelSlot* spacerTopLeft = UWidgetLayoutLibrary::SlotAsCanvasSlot( C_Spacer_TopLeft );
	if( spacerTopLeft != nullptr )
	{
		_MaxY = spacerTopLeft->GetPosition().Y;
	}

	UCanvasPanelSlot* spacerDownLeft = UWidgetLayoutLibrary::SlotAsCanvasSlot( C_Spacer_DownLeft );
	if( spacerDownLeft != nullptr )
	{
		_MinY = spacerDownLeft->GetPosition().Y;
		_MinX = spacerDownLeft->GetPosition().X;
	}

	UCanvasPanelSlot* spacerDownRight = UWidgetLayoutLibrary::SlotAsCanvasSlot( C_Spacer_DownRight );
	if( spacerDownRight != nullptr )
	{
		_MaxX = spacerDownRight->GetPosition().X;
	}
}
void UBWidget_PlayerChart::_SetPointBtnText( UTextBlock* dateText, UBButton* dateBtn, FString& dateString, FVector2D& btnPosition )
{
	if( dateText != nullptr )
	{
		dateText->SetText( FText::FromString( dateString ) );
	}

	if( dateBtn != nullptr )
	{
		UCanvasPanelSlot* pointBtn = UWidgetLayoutLibrary::SlotAsCanvasSlot( dateBtn );
		if( pointBtn != nullptr )
		{
			pointBtn->SetPosition( btnPosition );
			dateBtn->SetVisibility( ESlateVisibility::Visible );
		}
	}
}

void UBWidget_PlayerChart::_SetVisiblePointBtnText()
{
	C_Img_DotOver->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Day1->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Day2->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Day3->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Day4->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Day5->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Day6->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Day7->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Week1->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Week2->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Week3->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Week4->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Month1->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Month2->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Month3->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Month4->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Month5->SetVisibility( ESlateVisibility::Collapsed );
	C_Btn_Month6->SetVisibility( ESlateVisibility::Collapsed );

	switch( _PeriodFilterType )
	{
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_DAY:
		C_WidgetSwitcher_DateText->SetActiveWidgetIndex( 0 );
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_WEEK:
		C_WidgetSwitcher_DateText->SetActiveWidgetIndex( 1 );
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_MONTH:
		C_WidgetSwitcher_DateText->SetActiveWidgetIndex( 2 );
		break;
	default:
		break;
	}
}

void UBWidget_PlayerChart::SetChartDay()
{
	_SetVisiblePointBtnText();

	if( _ChartType == E_SORT_TYPE::E_SORT_TYPE_GOAL )
	{
		int32 maxGoalDataIndex = 0;
		uint32 minGoal = 99999999;
		uint32 maxGoal = 0;
		for( int32 index = 0; index < _DayMatchData.Num(); ++index )
		{
			if( _DayMatchData[index].Goal > maxGoal )
			{
				maxGoal = _DayMatchData[index].Goal;
				maxGoalDataIndex = index;
			}
			if( _DayMatchData[index].Goal < minGoal )
			{
				minGoal = _DayMatchData[index].Goal;
			}
		}

		float GoalGap = FMath::Max( uint32( 1 ), maxGoal - minGoal );
		float xGap = FMath::Max( 0.f, _MaxX - _MinX );
		float yGap = FMath::Max( 0.f, _MinY - _MaxY );
		float multiplyGaX = xGap / 7.f;
		float multiplyGaY = yGap / GoalGap;

		FVector2D pixelPosition;
		FVector2D viewportPosition;
		FGeometry geo = UWidgetLayoutLibrary::GetViewportWidgetGeometry( this->GetWorld() );
		_DatePoints.Empty();
		for( int32 matchIndex = 0; matchIndex < _DayMatchData.Num(); ++matchIndex )
		{
			FVector2D point( (multiplyGaX * (matchIndex + 1)) - (multiplyGaX * 0.5f),
							 FMath::Abs( ((_DayMatchData[matchIndex].Goal - minGoal) * multiplyGaY) + 100.f ) + 30.f );
			point.Y = C_SizeBox_Chart->HeightOverride - point.Y;
			_DatePoints.Add( point );
			USlateBlueprintLibrary::LocalToViewport( this->GetWorld(), geo, point, pixelPosition, viewportPosition );
			if( matchIndex == 0 ) _SetPointBtnText( C_Txt_Day1, C_Btn_Day1, _DayMatchData[matchIndex].DateDay, viewportPosition );
			else if( matchIndex == 1 ) _SetPointBtnText( C_Txt_Day2, C_Btn_Day2, _DayMatchData[matchIndex].DateDay, viewportPosition );
			else if( matchIndex == 2 ) _SetPointBtnText( C_Txt_Day3, C_Btn_Day3, _DayMatchData[matchIndex].DateDay, viewportPosition );
			else if( matchIndex == 3 ) _SetPointBtnText( C_Txt_Day4, C_Btn_Day4, _DayMatchData[matchIndex].DateDay, viewportPosition );
			else if( matchIndex == 4 ) _SetPointBtnText( C_Txt_Day5, C_Btn_Day5, _DayMatchData[matchIndex].DateDay, viewportPosition );
			else if( matchIndex == 5 ) _SetPointBtnText( C_Txt_Day6, C_Btn_Day6, _DayMatchData[matchIndex].DateDay, viewportPosition );
			else if( matchIndex == 6 ) _SetPointBtnText( C_Txt_Day7, C_Btn_Day7, _DayMatchData[matchIndex].DateDay, viewportPosition );

			if( maxGoalDataIndex == matchIndex )
			{
				UCanvasPanelSlot* lowPriceSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot( C_Txt_LowPrice );
				if( lowPriceSlot != nullptr )
				{
					point.Y += 50.f;
					lowPriceSlot->SetPosition( point );
					C_Txt_LowPrice->SetText( FText::AsNumber( maxGoal ) );
					C_Txt_LowPrice->SetVisibility( ESlateVisibility::Visible );
				}
			}
		}
	}
	else if( _ChartType == E_SORT_TYPE::E_SORT_TYPE_ASSIST )
	{
		int32 maxAssistDataIndex = 0;
		uint32 minAssist = 99999999;
		uint32 maxAssist = 0;
		for( int32 index = 0; index < _DayMatchData.Num(); ++index )
		{
			if( _DayMatchData[index].Assist > maxAssist )
			{
				maxAssist = _DayMatchData[index].Assist;
				maxAssistDataIndex = index;
			}
			if( _DayMatchData[index].Assist < minAssist )
			{
				minAssist = _DayMatchData[index].Assist;
			}
		}

		float AssistGap = FMath::Max( uint32( 1 ), maxAssist - minAssist );
		float xGap = FMath::Max( 0.f, _MaxX - _MinX );
		float yGap = FMath::Max( 0.f, _MinY - _MaxY );
		float multiplyGaX = xGap / 7.f;
		float multiplyGaY = yGap / AssistGap;

		FVector2D pixelPosition;
		FVector2D viewportPosition;
		FGeometry geo = UWidgetLayoutLibrary::GetViewportWidgetGeometry( this->GetWorld() );
		_DatePoints.Empty();
		for( int32 matchIndex = 0; matchIndex < _DayMatchData.Num(); ++matchIndex )
		{
			FVector2D point( (multiplyGaX * (matchIndex + 1)) - (multiplyGaX * 0.5f),
							 FMath::Abs( ((_DayMatchData[matchIndex].Assist - minAssist) * multiplyGaY) + 100.f ) + 30.f );
			point.Y = C_SizeBox_Chart->HeightOverride - point.Y;
			_DatePoints.Add( point );
			USlateBlueprintLibrary::LocalToViewport( this->GetWorld(), geo, point, pixelPosition, viewportPosition );
			if( matchIndex == 0 ) _SetPointBtnText( C_Txt_Day1, C_Btn_Day1, _DayMatchData[matchIndex].DateDay, viewportPosition );
			else if( matchIndex == 1 ) _SetPointBtnText( C_Txt_Day2, C_Btn_Day2, _DayMatchData[matchIndex].DateDay, viewportPosition );
			else if( matchIndex == 2 ) _SetPointBtnText( C_Txt_Day3, C_Btn_Day3, _DayMatchData[matchIndex].DateDay, viewportPosition );
			else if( matchIndex == 3 ) _SetPointBtnText( C_Txt_Day4, C_Btn_Day4, _DayMatchData[matchIndex].DateDay, viewportPosition );
			else if( matchIndex == 4 ) _SetPointBtnText( C_Txt_Day5, C_Btn_Day5, _DayMatchData[matchIndex].DateDay, viewportPosition );
			else if( matchIndex == 5 ) _SetPointBtnText( C_Txt_Day6, C_Btn_Day6, _DayMatchData[matchIndex].DateDay, viewportPosition );
			else if( matchIndex == 6 ) _SetPointBtnText( C_Txt_Day7, C_Btn_Day7, _DayMatchData[matchIndex].DateDay, viewportPosition );

			if( maxAssistDataIndex == matchIndex )
			{
				UCanvasPanelSlot* lowPriceSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot( C_Txt_LowPrice );
				if( lowPriceSlot != nullptr )
				{
					point.Y += 50.f;
					lowPriceSlot->SetPosition( point );
					C_Txt_LowPrice->SetText( FText::AsNumber( maxAssist ) );
					C_Txt_LowPrice->SetVisibility( ESlateVisibility::Visible );
				}
			}
		}
	}	
}

void UBWidget_PlayerChart::SetChartWeek()
{
	_SetVisiblePointBtnText();

	if( _ChartType == E_SORT_TYPE::E_SORT_TYPE_GOAL )
	{
		int32 maxGoalDataIndex = 0;
		uint32 minGoal = 99999999;
		uint32 maxGoal = 0;
		for( int32 index = 0; index < _WeekMatchData.Num(); ++index )
		{
			if( _WeekMatchData[index].Goal > maxGoal )
			{
				maxGoal = _WeekMatchData[index].Goal;
				maxGoalDataIndex = index;
			}
			if( _WeekMatchData[index].Goal < minGoal )
			{
				minGoal = _WeekMatchData[index].Goal;
			}
		}

		float GoalGap = FMath::Max( uint32( 1 ), maxGoal - minGoal );
		float xGap = FMath::Max( 0.f, _MaxX - _MinX );
		float yGap = FMath::Max( 0.f, _MinY - _MaxY );
		float multiplyGaX = xGap / 4.f;
		float multiplyGaY = yGap / GoalGap;

		FVector2D pixelPosition;
		FVector2D viewportPosition;
		FGeometry geo = UWidgetLayoutLibrary::GetViewportWidgetGeometry( this->GetWorld() );
		_DatePoints.Empty();
		for( int32 matchIndex = 0; matchIndex < _WeekMatchData.Num(); ++matchIndex )
		{
			FVector2D point( (multiplyGaX * (matchIndex + 1)) - (multiplyGaX * 0.5f),
							 FMath::Abs( ((_WeekMatchData[matchIndex].Goal - minGoal) * multiplyGaY) + 100.f ) + 30.f );
			point.Y = C_SizeBox_Chart->HeightOverride - point.Y;
			_DatePoints.Add( point );
			USlateBlueprintLibrary::LocalToViewport( this->GetWorld(), geo, point, pixelPosition, viewportPosition );
			if( matchIndex == 0 ) _SetPointBtnText( C_Txt_Week1, C_Btn_Week1, _WeekMatchData[matchIndex].Date, viewportPosition );
			else if( matchIndex == 1 ) _SetPointBtnText( C_Txt_Week2, C_Btn_Week2, _WeekMatchData[matchIndex].Date, viewportPosition );
			else if( matchIndex == 2 ) _SetPointBtnText( C_Txt_Week3, C_Btn_Week3, _WeekMatchData[matchIndex].Date, viewportPosition );
			else if( matchIndex == 3 ) _SetPointBtnText( C_Txt_Week4, C_Btn_Week4, _WeekMatchData[matchIndex].Date, viewportPosition );

			if( maxGoalDataIndex == matchIndex )
			{
				UCanvasPanelSlot* lowPriceSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot( C_Txt_LowPrice );
				if( lowPriceSlot != nullptr )
				{
					point.Y += 50.f;
					lowPriceSlot->SetPosition( point );
					C_Txt_LowPrice->SetText( FText::AsNumber( maxGoal ) );
					C_Txt_LowPrice->SetVisibility( ESlateVisibility::Visible );
				}
			}
		}
	}
	else if( _ChartType == E_SORT_TYPE::E_SORT_TYPE_ASSIST )
	{
		int32 maxGoalDataIndex = 0;
		uint32 minGoal = 99999999;
		uint32 maxGoal = 0;
		for( int32 index = 0; index < _WeekMatchData.Num(); ++index )
		{
			if( _WeekMatchData[index].Assist > maxGoal )
			{
				maxGoal = _WeekMatchData[index].Assist;
				maxGoalDataIndex = index;
			}
			if( _WeekMatchData[index].Assist < minGoal )
			{
				minGoal = _WeekMatchData[index].Assist;
			}
		}

		float GoalGap = FMath::Max( uint32( 1 ), maxGoal - minGoal );
		float xGap = FMath::Max( 0.f, _MaxX - _MinX );
		float yGap = FMath::Max( 0.f, _MinY - _MaxY );
		float multiplyGaX = xGap / 4.f;
		float multiplyGaY = yGap / GoalGap;

		FVector2D pixelPosition;
		FVector2D viewportPosition;
		FGeometry geo = UWidgetLayoutLibrary::GetViewportWidgetGeometry( this->GetWorld() );
		_DatePoints.Empty();
		for( int32 matchIndex = 0; matchIndex < _WeekMatchData.Num(); ++matchIndex )
		{
			FVector2D point( (multiplyGaX * (matchIndex + 1)) - (multiplyGaX * 0.5f),
							 FMath::Abs( ((_WeekMatchData[matchIndex].Assist - minGoal) * multiplyGaY) + 100.f ) + 30.f );
			point.Y = C_SizeBox_Chart->HeightOverride - point.Y;
			_DatePoints.Add( point );
			USlateBlueprintLibrary::LocalToViewport( this->GetWorld(), geo, point, pixelPosition, viewportPosition );
			if( matchIndex == 0 ) _SetPointBtnText( C_Txt_Week1, C_Btn_Week1, _WeekMatchData[matchIndex].Date, viewportPosition );
			else if( matchIndex == 1 ) _SetPointBtnText( C_Txt_Week2, C_Btn_Week2, _WeekMatchData[matchIndex].Date, viewportPosition );
			else if( matchIndex == 2 ) _SetPointBtnText( C_Txt_Week3, C_Btn_Week3, _WeekMatchData[matchIndex].Date, viewportPosition );
			else if( matchIndex == 3 ) _SetPointBtnText( C_Txt_Week4, C_Btn_Week4, _WeekMatchData[matchIndex].Date, viewportPosition );

			if( maxGoalDataIndex == matchIndex )
			{
				UCanvasPanelSlot* lowPriceSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot( C_Txt_LowPrice );
				if( lowPriceSlot != nullptr )
				{
					point.Y += 50.f;
					lowPriceSlot->SetPosition( point );
					C_Txt_LowPrice->SetText( FText::AsNumber( maxGoal ) );
					C_Txt_LowPrice->SetVisibility( ESlateVisibility::Visible );
				}
			}
		}
	}
}

void UBWidget_PlayerChart::SetChartMonth()
{
	_SetVisiblePointBtnText();

	if( _ChartType == E_SORT_TYPE::E_SORT_TYPE_GOAL )
	{
		int32 maxGoalDataIndex = 0;
		uint32 minGoal = 99999999;
		uint32 maxGoal = 0;
		for( int32 index = 0; index < _MonthMatchData.Num(); ++index )
		{
			if( _MonthMatchData[index].Goal > maxGoal )
			{
				maxGoal = _MonthMatchData[index].Goal;
				maxGoalDataIndex = index;
			}
			if( _MonthMatchData[index].Goal < minGoal )
			{
				minGoal = _MonthMatchData[index].Goal;
			}
		}

		_PriceGap = FMath::Max( uint32( 1 ), maxGoal - minGoal );
		float xGap = FMath::Max( 0.f, _MaxX - _MinX );
		float yGap = FMath::Max( 0.f, _MinY - _MaxY );
		float multiplyGaX = xGap / 6.f;
		float multiplyGaY = yGap / _PriceGap;

		FVector2D pixelPosition;
		FVector2D viewportPosition;
		FGeometry geo = UWidgetLayoutLibrary::GetViewportWidgetGeometry( this->GetWorld() );
		_DatePoints.Empty();
		for( int32 matchIndex = 0; matchIndex < _MonthMatchData.Num(); ++matchIndex )
		{
			FVector2D point( (multiplyGaX * (matchIndex + 1)) - (multiplyGaX * 0.5f),
							 FMath::Abs( ((_MonthMatchData[matchIndex].Goal - minGoal) * multiplyGaY) + 100.f ) + 30.f );
			point.Y = C_SizeBox_Chart->HeightOverride - point.Y;
			_DatePoints.Add( point );
			USlateBlueprintLibrary::LocalToViewport( this->GetWorld(), geo, point, pixelPosition, viewportPosition );

			if( matchIndex == 0 ) _SetPointBtnText( C_Txt_Month1, C_Btn_Month1, _MonthMatchData[matchIndex].DateMonth, viewportPosition );
			else if( matchIndex == 1 ) _SetPointBtnText( C_Txt_Month2, C_Btn_Month2, _MonthMatchData[matchIndex].DateMonth, viewportPosition );
			else if( matchIndex == 2 ) _SetPointBtnText( C_Txt_Month3, C_Btn_Month3, _MonthMatchData[matchIndex].DateMonth, viewportPosition );
			else if( matchIndex == 3 ) _SetPointBtnText( C_Txt_Month4, C_Btn_Month4, _MonthMatchData[matchIndex].DateMonth, viewportPosition );
			else if( matchIndex == 4 ) _SetPointBtnText( C_Txt_Month5, C_Btn_Month5, _MonthMatchData[matchIndex].DateMonth, viewportPosition );
			else if( matchIndex == 5 ) _SetPointBtnText( C_Txt_Month6, C_Btn_Month6, _MonthMatchData[matchIndex].DateMonth, viewportPosition );

			if( maxGoalDataIndex == matchIndex )
			{
				UCanvasPanelSlot* lowPriceSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot( C_Txt_LowPrice );
				if( lowPriceSlot != nullptr )
				{
					point.Y += 50.f;
					lowPriceSlot->SetPosition( point );
					C_Txt_LowPrice->SetText( FText::AsNumber( maxGoal ) );
					C_Txt_LowPrice->SetVisibility( ESlateVisibility::Visible );
				}
			}
		}
	}
	else if( _ChartType == E_SORT_TYPE::E_SORT_TYPE_ASSIST )
	{
		int32 maxAssistDataIndex = 0;
		uint32 minAssist = 99999999;
		uint32 maxAssist = 0;
		for( int32 index = 0; index < _MonthMatchData.Num(); ++index )
		{
			if( _MonthMatchData[index].Assist > maxAssist )
			{
				maxAssist = _MonthMatchData[index].Assist;
				maxAssistDataIndex = index;
			}
			if( _MonthMatchData[index].Assist < minAssist )
			{
				minAssist = _MonthMatchData[index].Assist;
			}
		}

		_PriceGap = FMath::Max( uint32( 1 ), maxAssist - minAssist );
		float xGap = FMath::Max( 0.f, _MaxX - _MinX );
		float yGap = FMath::Max( 0.f, _MinY - _MaxY );
		float multiplyGaX = xGap / 6.f;
		float multiplyGaY = yGap / _PriceGap;

		FVector2D pixelPosition;
		FVector2D viewportPosition;
		FGeometry geo = UWidgetLayoutLibrary::GetViewportWidgetGeometry( this->GetWorld() );
		_DatePoints.Empty();
		for( int32 matchIndex = 0; matchIndex < _MonthMatchData.Num(); ++matchIndex )
		{
			FVector2D point( (multiplyGaX * (matchIndex + 1)) - (multiplyGaX * 0.5f),
							 FMath::Abs( ((_MonthMatchData[matchIndex].Assist - minAssist) * multiplyGaY) + 100.f ) + 30.f );
			point.Y = C_SizeBox_Chart->HeightOverride - point.Y;
			_DatePoints.Add( point );
			USlateBlueprintLibrary::LocalToViewport( this->GetWorld(), geo, point, pixelPosition, viewportPosition );

			if( matchIndex == 0 ) _SetPointBtnText( C_Txt_Month1, C_Btn_Month1, _MonthMatchData[matchIndex].DateMonth, viewportPosition );
			else if( matchIndex == 1 ) _SetPointBtnText( C_Txt_Month2, C_Btn_Month2, _MonthMatchData[matchIndex].DateMonth, viewportPosition );
			else if( matchIndex == 2 ) _SetPointBtnText( C_Txt_Month3, C_Btn_Month3, _MonthMatchData[matchIndex].DateMonth, viewportPosition );
			else if( matchIndex == 3 ) _SetPointBtnText( C_Txt_Month4, C_Btn_Month4, _MonthMatchData[matchIndex].DateMonth, viewportPosition );
			else if( matchIndex == 4 ) _SetPointBtnText( C_Txt_Month5, C_Btn_Month5, _MonthMatchData[matchIndex].DateMonth, viewportPosition );
			else if( matchIndex == 5 ) _SetPointBtnText( C_Txt_Month6, C_Btn_Month6, _MonthMatchData[matchIndex].DateMonth, viewportPosition );

			if( maxAssistDataIndex == matchIndex )
			{
				UCanvasPanelSlot* lowPriceSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot( C_Txt_LowPrice );
				if( lowPriceSlot != nullptr )
				{
					point.Y += 50.f;
					lowPriceSlot->SetPosition( point );
					C_Txt_LowPrice->SetText( FText::AsNumber( maxAssist ) );
					C_Txt_LowPrice->SetVisibility( ESlateVisibility::Visible );
				}
			}
		}
	}
}

void UBWidget_PlayerChart::OnClickPeriodFilter( const E_FILTER_ITEM_TYPE periodFilterType, bool isForce /*= true */ )
{
	if( isForce == false && _PeriodFilterType == periodFilterType )
	{
		return;
	}

	_PeriodFilterType = periodFilterType;

	C_Txt_ClickPrice->SetVisibility( ESlateVisibility::Collapsed );
	C_Txt_LowPrice->SetVisibility( ESlateVisibility::Collapsed );

	switch( periodFilterType )
	{
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_DAY:
		BP_Day_UMG->SelectDetailInfoFilterItem( true );
		BP_Week_UMG->SelectDetailInfoFilterItem( false );
		BP_Month_UMG->SelectDetailInfoFilterItem( false );
		if( !isForce )
			SetChartDay();
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_WEEK:
		BP_Day_UMG->SelectDetailInfoFilterItem( false );
		BP_Week_UMG->SelectDetailInfoFilterItem( true );
		BP_Month_UMG->SelectDetailInfoFilterItem( false );
		if( !isForce )
			SetChartWeek();
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_MONTH:
		BP_Day_UMG->SelectDetailInfoFilterItem( false );
		BP_Week_UMG->SelectDetailInfoFilterItem( false );
		BP_Month_UMG->SelectDetailInfoFilterItem( true );
		if( !isForce )
			SetChartMonth();
		break;
	default:
		break;
	}
}

void UBWidget_PlayerChart::_DrawChartDay( FPaintContext& Context ) const
{
	if( _DatePoints.Num() > 0 )
	{
		UWidgetBlueprintLibrary::DrawLines( Context, _DatePoints, Color_BootsCompare_Blue, true, 2.f );
	}
}

