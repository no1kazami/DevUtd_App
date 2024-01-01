// Fill out your copyright notice in the Description page of Project Settings.


#include "BWidget_ShopChart.h"
#include "UI/Equip/BWidget_EquipFilterItem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Bigtamin.h"

void UBWidget_ShopChart::Init()
{
	Super::Init();

	ButtonDelegate_Clicked( this, C_Btn_Day1, &UBWidget_ShopChart::_OnClick_Day1 );
	ButtonDelegate_Clicked( this, C_Btn_Day2, &UBWidget_ShopChart::_OnClick_Day2 );
	ButtonDelegate_Clicked( this, C_Btn_Day3, &UBWidget_ShopChart::_OnClick_Day3 );
	ButtonDelegate_Clicked( this, C_Btn_Day4, &UBWidget_ShopChart::_OnClick_Day4 );
	ButtonDelegate_Clicked( this, C_Btn_Day5, &UBWidget_ShopChart::_OnClick_Day5 );
	ButtonDelegate_Clicked( this, C_Btn_Day6, &UBWidget_ShopChart::_OnClick_Day6 );
	ButtonDelegate_Clicked( this, C_Btn_Day7, &UBWidget_ShopChart::_OnClick_Day7 );

	ButtonDelegate_Clicked( this, C_Btn_Week1, &UBWidget_ShopChart::_OnClick_Week1 );
	ButtonDelegate_Clicked( this, C_Btn_Week2, &UBWidget_ShopChart::_OnClick_Week2 );
	ButtonDelegate_Clicked( this, C_Btn_Week3, &UBWidget_ShopChart::_OnClick_Week3 );
	ButtonDelegate_Clicked( this, C_Btn_Week4, &UBWidget_ShopChart::_OnClick_Week4 );
	
	ButtonDelegate_Clicked( this, C_Btn_Month1, &UBWidget_ShopChart::_OnClick_Month1 );
	ButtonDelegate_Clicked( this, C_Btn_Month2, &UBWidget_ShopChart::_OnClick_Month2 );
	ButtonDelegate_Clicked( this, C_Btn_Month3, &UBWidget_ShopChart::_OnClick_Month3 );
	ButtonDelegate_Clicked( this, C_Btn_Month4, &UBWidget_ShopChart::_OnClick_Month4 );
	ButtonDelegate_Clicked( this, C_Btn_Month5, &UBWidget_ShopChart::_OnClick_Month5 );
	ButtonDelegate_Clicked( this, C_Btn_Month6, &UBWidget_ShopChart::_OnClick_Month6 );

	BP_Day_UMG->Init();
	BP_Day_UMG->SetDetailInfoFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_DAY, 64 );
	if( BP_Day_UMG->OnClickDetailInfoFilter.IsBoundToObject( this ) == false )
	{
		BP_Day_UMG->OnClickDetailInfoFilter.AddUObject( this, &UBWidget_ShopChart::OnClickPeriodFilter );
	}
	BP_Week_UMG->Init();
	BP_Week_UMG->SetDetailInfoFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_WEEK, 65 );
	if( BP_Week_UMG->OnClickDetailInfoFilter.IsBoundToObject( this ) == false )
	{
		BP_Week_UMG->OnClickDetailInfoFilter.AddUObject( this, &UBWidget_ShopChart::OnClickPeriodFilter );
	}
	BP_Month_UMG->Init();
	BP_Month_UMG->SetDetailInfoFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_MONTH, 66 );
	if( BP_Month_UMG->OnClickDetailInfoFilter.IsBoundToObject( this ) == false )
	{
		BP_Month_UMG->OnClickDetailInfoFilter.AddUObject( this, &UBWidget_ShopChart::OnClickPeriodFilter );
	}

	OnClickPeriodFilter( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_DAY, true );

	_ShopProductID.Empty();
	_CalcChartBaseData();
}

void UBWidget_ShopChart::OnClose()
{
	Super::OnClose();
}


int32 UBWidget_ShopChart::NativePaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const
{
	FPaintContext Context( AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled );
	_DrawChartDay( Context );

	return Super::NativePaint( Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled );
}

void UBWidget_ShopChart::SetShopData( const FString shopProductID )
{
	_ShopProductID = shopProductID;

	const FST_BOOTS_CRAWLING_DATA* crawlingData = UFBM_SaveGame::Get().GetBootsCrawlingData( _ShopProductID );
	if( crawlingData != nullptr )
	{
		for( auto& lowDayPriceInfo : crawlingData->LowPriceDay )
		{
			_DayPriceData.Add( FST_LOW_PRICE_INFO_DATA( lowDayPriceInfo.Key, lowDayPriceInfo.Value ) );
		}
		for( auto& lowWeekPriceInfo : crawlingData->LowPriceWeek )
		{
			_WeekPriceData.Add( FST_LOW_PRICE_INFO_DATA( lowWeekPriceInfo.Key, lowWeekPriceInfo.Value ) );
		}
		for( auto& lowMonthPriceInfo : crawlingData->LowPriceMonth )
		{
			_MonthPriceData.Add( FST_LOW_PRICE_INFO_DATA( lowMonthPriceInfo.Key, lowMonthPriceInfo.Value ) );
		}
	}

	_TestData();
}

void UBWidget_ShopChart::_CalcCurPriceTextPosition( UBButton* btn, int32 dataIndex)
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

				E_CRAWLING_WEBPAGE shopData;
				uint32 priceData;
				switch( _PeriodFilterType )
				{
				case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_DAY:
					shopData = _DayPriceData[dataIndex].ShopData;
					priceData = _DayPriceData[dataIndex].PriceData;
					break;
				case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_WEEK:
					shopData = _WeekPriceData[dataIndex].ShopData;
					priceData = _WeekPriceData[dataIndex].PriceData;
					break;
				case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_MONTH:
					shopData = _MonthPriceData[dataIndex].ShopData;
					priceData = _MonthPriceData[dataIndex].PriceData;
					break;
				default:
					shopData = E_CRAWLING_WEBPAGE::NONE;
					priceData = 0;
					break;
				}

				FText shopText = UFBMUtil::ShopNameText( shopData );
				C_Txt_ClickPrice->SetText( FText::Format( GET_BTEXT( 63 ), FText::AsNumber( priceData ), shopText ) );
				C_Txt_ClickPrice->SetVisibility( ESlateVisibility::Visible );
			}
		}
	}
}

void UBWidget_ShopChart::_TestData()
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
	/////////////////////////////////////////////////
#endif
}

void UBWidget_ShopChart::_OnClick_Day1()
{
	if( _DayPriceData.IsValidIndex( 0 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Day1, 0 );
	}
}

void UBWidget_ShopChart::_OnClick_Day2()
{
	if( _DayPriceData.IsValidIndex( 1 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Day2, 1 );
	}
}

void UBWidget_ShopChart::_OnClick_Day3()
{
	if( _DayPriceData.IsValidIndex( 2 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Day3, 2);
	}
}

void UBWidget_ShopChart::_OnClick_Day4()
{
	if( _DayPriceData.IsValidIndex( 3 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Day4, 3 );
	}
}

void UBWidget_ShopChart::_OnClick_Day5()
{
	if( _DayPriceData.IsValidIndex( 4 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Day5, 4 );
	}
}

void UBWidget_ShopChart::_OnClick_Day6()
{
	if( _DayPriceData.IsValidIndex( 5 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Day6, 5 );
	}
}

void UBWidget_ShopChart::_OnClick_Day7()
{
	if( _DayPriceData.IsValidIndex( 6 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Day7, 6 );
	}
}

void UBWidget_ShopChart::_OnClick_Week1()
{
	if( _WeekPriceData.IsValidIndex( 0 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Week1, 0 );
	}
}

void UBWidget_ShopChart::_OnClick_Week2()
{
	if( _WeekPriceData.IsValidIndex( 1 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Week2, 1 );
	}
}

void UBWidget_ShopChart::_OnClick_Week3()
{
	if( _WeekPriceData.IsValidIndex( 2 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Week3, 2 );
	}
}

void UBWidget_ShopChart::_OnClick_Week4()
{
	if( _WeekPriceData.IsValidIndex( 3 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Week4, 3 );
	}
}

void UBWidget_ShopChart::_OnClick_Month1()
{
	if( _MonthPriceData.IsValidIndex( 0 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Month1, 0 );
	}
}

void UBWidget_ShopChart::_OnClick_Month2()
{
	if( _MonthPriceData.IsValidIndex( 1 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Month2, 1);
	}
}

void UBWidget_ShopChart::_OnClick_Month3()
{
	if( _MonthPriceData.IsValidIndex( 2 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Month3, 2 );
	}
}

void UBWidget_ShopChart::_OnClick_Month4()
{
	if( _MonthPriceData.IsValidIndex( 3 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Month4, 3 );
	}
}

void UBWidget_ShopChart::_OnClick_Month5()
{
	if( _MonthPriceData.IsValidIndex( 4 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Month5, 4 );
	}
}

void UBWidget_ShopChart::_OnClick_Month6()
{
	if( _MonthPriceData.IsValidIndex( 5 ) )
	{
		_CalcCurPriceTextPosition( C_Btn_Month6, 5 );
	}
}

void UBWidget_ShopChart::_CalcChartBaseData()
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
void UBWidget_ShopChart::_SetPointBtnText( UTextBlock* dateText, UBButton* dateBtn, FString& dateString, FVector2D& btnPosition )
{
	if( dateText != nullptr )
	{
		dateText->SetText( FText::FromString( dateString ) );
	}

	if ( dateBtn != nullptr)
	{
		UCanvasPanelSlot* pointBtn = UWidgetLayoutLibrary::SlotAsCanvasSlot( dateBtn );
		if( pointBtn != nullptr )
		{
			pointBtn->SetPosition( btnPosition );
			dateBtn->SetVisibility( ESlateVisibility::Visible );
		}
	}
}

void UBWidget_ShopChart::_SetVisiblePointBtnText()
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

void UBWidget_ShopChart::SetChartDay()
{
	_SetVisiblePointBtnText();

	int32 minPriceDataIndex = 0;
	uint32 minPrice = 99999999;
	uint32 maxPrice = 0;
	for( int32 index = 0; index < _DayPriceData.Num(); ++index )
	{
		if( _DayPriceData[index].PriceData > maxPrice )
		{
			maxPrice = _DayPriceData[index].PriceData;
		}
		if( _DayPriceData[index].PriceData < minPrice )
		{
			minPrice = _DayPriceData[index].PriceData;
			minPriceDataIndex = index;
		}
	}

	_PriceGap = FMath::Max( uint32(1), maxPrice - minPrice );
	float xGap = FMath::Max( 0.f, _MaxX - _MinX);
	float yGap = FMath::Max( 0.f, _MinY - _MaxY);
	float multiplyGaX = xGap / 7.f;
	float multiplyGaY = yGap / _PriceGap;

	FVector2D pixelPosition;
	FVector2D viewportPosition;
	FGeometry geo = UWidgetLayoutLibrary::GetViewportWidgetGeometry(this->GetWorld());
	_DatePoints.Empty();
	for( int32 priceIndex = 0; priceIndex < _DayPriceData.Num(); ++priceIndex )
	{
		FVector2D point( (multiplyGaX * (priceIndex + 1)) - (multiplyGaX * 0.5f),
						 FMath::Abs( ((_DayPriceData[priceIndex].PriceData - minPrice) * multiplyGaY) + 100.f) + 30.f );
		point.Y = C_SizeBox_Chart->HeightOverride - point.Y;
		_DatePoints.Add( point );
		USlateBlueprintLibrary::LocalToViewport( this->GetWorld(), geo, point, pixelPosition, viewportPosition );
		if( priceIndex == 0 ) _SetPointBtnText( C_Txt_Day1, C_Btn_Day1, _DayPriceData[priceIndex].Date, viewportPosition );
		else if( priceIndex == 1 ) _SetPointBtnText( C_Txt_Day2, C_Btn_Day2, _DayPriceData[priceIndex].Date, viewportPosition );
		else if( priceIndex == 2 ) _SetPointBtnText( C_Txt_Day3, C_Btn_Day3, _DayPriceData[priceIndex].Date, viewportPosition );
		else if( priceIndex == 3 ) _SetPointBtnText( C_Txt_Day4, C_Btn_Day4, _DayPriceData[priceIndex].Date, viewportPosition );
		else if( priceIndex == 4 ) _SetPointBtnText( C_Txt_Day5, C_Btn_Day5, _DayPriceData[priceIndex].Date, viewportPosition );
		else if( priceIndex == 5 ) _SetPointBtnText( C_Txt_Day6, C_Btn_Day6, _DayPriceData[priceIndex].Date, viewportPosition );
		else if( priceIndex == 6 ) _SetPointBtnText( C_Txt_Day7, C_Btn_Day7, _DayPriceData[priceIndex].Date, viewportPosition );

		if( minPriceDataIndex == priceIndex )
		{
			UCanvasPanelSlot* lowPriceSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot( C_Txt_LowPrice );
			if( lowPriceSlot != nullptr )
			{
				point.Y += 50.f;
				lowPriceSlot->SetPosition( point );
				C_Txt_LowPrice->SetText( FText::AsNumber( minPrice ) );
				C_Txt_LowPrice->SetVisibility( ESlateVisibility::Visible );
			}
		}
	}
}

void UBWidget_ShopChart::SetChartWeek()
{
	_SetVisiblePointBtnText();

	int32 minPriceDataIndex = 0;
	uint32 minPrice = 99999999;
	uint32 maxPrice = 0;
	for( int32 index = 0; index < _WeekPriceData.Num(); ++index )
	{
		if( _WeekPriceData[index].PriceData > maxPrice )
		{
			maxPrice = _WeekPriceData[index].PriceData;
		}
		if( _WeekPriceData[index].PriceData < minPrice )
		{
			minPrice = _WeekPriceData[index].PriceData;
			minPriceDataIndex = index;
		}
	}

	_PriceGap = FMath::Max( uint32( 1 ), maxPrice - minPrice );
	float xGap = FMath::Max( 0.f, _MaxX - _MinX );
	float yGap = FMath::Max( 0.f, _MinY - _MaxY );
	float multiplyGaX = xGap / 4.f;
	float multiplyGaY = yGap / _PriceGap;

	FVector2D pixelPosition;
	FVector2D viewportPosition;
	FGeometry geo = UWidgetLayoutLibrary::GetViewportWidgetGeometry( this->GetWorld() );
	_DatePoints.Empty();
	for( int32 priceIndex = 0; priceIndex < _WeekPriceData.Num(); ++priceIndex )
	{
		FVector2D point( (multiplyGaX * (priceIndex + 1)) - (multiplyGaX * 0.5f),
						 FMath::Abs( ((_WeekPriceData[priceIndex].PriceData - minPrice) * multiplyGaY) + 100.f ) + 30.f );
		point.Y = C_SizeBox_Chart->HeightOverride - point.Y;
		_DatePoints.Add( point );
		USlateBlueprintLibrary::LocalToViewport( this->GetWorld(), geo, point, pixelPosition, viewportPosition );

		FString priceDate = _WeekPriceData[priceIndex].Date;
		FString strYear = priceDate.Left( 2 );
		FString strWeek = priceDate.Right( 2 );
		priceDate = FText::Format( GET_BTEXT( 85 ), FText::FromString( strYear ), FText::FromString( strWeek ) ).ToString();

		if( priceIndex == 0 ) _SetPointBtnText( C_Txt_Week1, C_Btn_Week1, priceDate, viewportPosition );
		else if( priceIndex == 1 ) _SetPointBtnText( C_Txt_Week2, C_Btn_Week2, priceDate, viewportPosition );
		else if( priceIndex == 2 ) _SetPointBtnText( C_Txt_Week3, C_Btn_Week3, priceDate, viewportPosition );
		else if( priceIndex == 3 ) _SetPointBtnText( C_Txt_Week4, C_Btn_Week4, priceDate, viewportPosition );

		if( minPriceDataIndex == priceIndex )
		{
			UCanvasPanelSlot* lowPriceSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot( C_Txt_LowPrice );
			if( lowPriceSlot != nullptr )
			{
				point.Y += 50.f;
				lowPriceSlot->SetPosition( point );
				C_Txt_LowPrice->SetText( FText::AsNumber( minPrice ) );
				C_Txt_LowPrice->SetVisibility( ESlateVisibility::Visible );
			}
		}
	}
}

void UBWidget_ShopChart::SetChartMonth()
{
	_SetVisiblePointBtnText();

	int32 minPriceDataIndex = 0;
	uint32 minPrice = 99999999;
	uint32 maxPrice = 0;
	for( int32 index = 0; index < _MonthPriceData.Num(); ++index )
	{
		if( _MonthPriceData[index].PriceData > maxPrice )
		{
			maxPrice = _MonthPriceData[index].PriceData;
		}
		if( _MonthPriceData[index].PriceData < minPrice )
		{
			minPrice = _MonthPriceData[index].PriceData;
			minPriceDataIndex = index;
		}
	}

	_PriceGap = FMath::Max( uint32( 1 ), maxPrice - minPrice );
	float xGap = FMath::Max( 0.f, _MaxX - _MinX );
	float yGap = FMath::Max( 0.f, _MinY - _MaxY );
	float multiplyGaX = xGap / 6.f;
	float multiplyGaY = yGap / _PriceGap;

	FVector2D pixelPosition;
	FVector2D viewportPosition;
	FGeometry geo = UWidgetLayoutLibrary::GetViewportWidgetGeometry( this->GetWorld() );
	_DatePoints.Empty();
	for( int32 priceIndex = 0; priceIndex < _MonthPriceData.Num(); ++priceIndex )
	{
		FVector2D point( (multiplyGaX * (priceIndex + 1)) - (multiplyGaX * 0.5f),
						 FMath::Abs( ((_MonthPriceData[priceIndex].PriceData - minPrice) * multiplyGaY) + 100.f ) + 30.f );
		point.Y = C_SizeBox_Chart->HeightOverride - point.Y;
		_DatePoints.Add( point );
		USlateBlueprintLibrary::LocalToViewport( this->GetWorld(), geo, point, pixelPosition, viewportPosition );

		if( priceIndex == 0 ) _SetPointBtnText( C_Txt_Month1, C_Btn_Month1, _MonthPriceData[priceIndex].Date, viewportPosition );
		else if( priceIndex == 1 ) _SetPointBtnText( C_Txt_Month2, C_Btn_Month2, _MonthPriceData[priceIndex].Date, viewportPosition );
		else if( priceIndex == 2 ) _SetPointBtnText( C_Txt_Month3, C_Btn_Month3, _MonthPriceData[priceIndex].Date, viewportPosition );
		else if( priceIndex == 3 ) _SetPointBtnText( C_Txt_Month4, C_Btn_Month4, _MonthPriceData[priceIndex].Date, viewportPosition );
		else if( priceIndex == 4 ) _SetPointBtnText( C_Txt_Month5, C_Btn_Month5, _MonthPriceData[priceIndex].Date, viewportPosition );
		else if( priceIndex == 5 ) _SetPointBtnText( C_Txt_Month6, C_Btn_Month6, _MonthPriceData[priceIndex].Date, viewportPosition );

		if( minPriceDataIndex == priceIndex )
		{
			UCanvasPanelSlot* lowPriceSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot( C_Txt_LowPrice );
			if( lowPriceSlot != nullptr )
			{
				point.Y += 50.f;
				lowPriceSlot->SetPosition( point );
				C_Txt_LowPrice->SetText( FText::AsNumber( minPrice ) );
				C_Txt_LowPrice->SetVisibility( ESlateVisibility::Visible );
			}
		}
	}
}

void UBWidget_ShopChart::OnClickPeriodFilter( const E_FILTER_ITEM_TYPE periodFilterType, bool isForce /*= true */ )
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

void UBWidget_ShopChart::_DrawChartDay( FPaintContext& Context ) const
{
	if ( _DatePoints.Num() > 0)
	{
		UWidgetBlueprintLibrary::DrawLines( Context, _DatePoints, Color_BootsCompare_Blue, true, 2.f );
	}
}

