#include "BWidget_RankingMain.h"
#include "Bigtamin.h"
#include "BWidget_RankingSort.h"
#include "BWidget_RankingFilter.h"
#include "UI/Equip/BWidget_EquipFilterItem.h"
#include "BWidget_RankingTop3.h"
#include "BWidget_RankingSlot.h"

void UBWidget_RankingMain::Init()
{
	Super::Init();

	BP_Top_RankingMain_UMG->Init();
	BP_Top_RankingMain_UMG->ChangeTopMode( E_MODE::E_MODE_RANKING_MAIN );

	BP_RankingSort_UMG->Init();
	BP_RankingSort_UMG->SetVisibility( ESlateVisibility::Collapsed );
	if( BP_RankingSort_UMG->OnClickRankingSort.IsBoundToObject( this ) == false )
	{
		BP_RankingSort_UMG->OnClickRankingSort.AddUObject( this, &UBWidget_RankingMain::_OnClickRankingSortEvent );
	}

	BP_RankingFilter_UMG->Init( this );
	BP_RankingFilter_UMG->SetVisibility( ESlateVisibility::Collapsed );
	if( BP_RankingFilter_UMG->OnClickRankingFilterApply.IsBoundToObject( this ) == false )
	{
		BP_RankingFilter_UMG->OnClickRankingFilterApply.AddUObject( this, &UBWidget_RankingMain::_OnClickRankingFilterApplyEvent );
	}
	if( BP_RankingFilter_UMG->OnClickRankingFilterCancel.IsBoundToObject( this ) == false )
	{
		BP_RankingFilter_UMG->OnClickRankingFilterCancel.AddUObject( this, &UBWidget_RankingMain::_OnClickRankingFilterCancelEvent );
	}

	ButtonDelegate_Clicked( this, C_Btn_Year_Prev, &UBWidget_RankingMain::_OnClick_YearPrevBtn );
	ButtonDelegate_Clicked( this, C_Btn_Year_Next, &UBWidget_RankingMain::_OnClick_YearNextBtn );
	ButtonDelegate_Clicked( this, C_Btn_Sort, &UBWidget_RankingMain::_OnClick_SortBtn );
	ButtonDelegate_Clicked( this, C_Btn_Filter, &UBWidget_RankingMain::_OnClick_FilterBtn );
	ButtonDelegate_Clicked( this, C_Btn_ExceptionStadium, &UBWidget_RankingMain::_OnClick_ExceptionStadiumBtn );

	C_CB_ExceptionStadium->OnCheckStateChanged.RemoveDynamic( this, &UBWidget_RankingMain::_OnExceptionStadiumCheckStateChanged );
	C_CB_ExceptionStadium->OnCheckStateChanged.AddDynamic( this, &UBWidget_RankingMain::_OnExceptionStadiumCheckStateChanged );

	InitRankingMain();

	_Ani_FilterOpen = GetWidgetAnimation( _Ani_FilterOpenName );
	Ani_FilterClose = GetWidgetAnimation( _Ani_FilterCloseName );
	_Ani_RankingMainOpen = GetWidgetAnimation( _Ani_RankingMainOpenName );
	_Ani_RankingMainClose = GetWidgetAnimation( _Ani_RankingMainCloseName );

	GInst->AddBackInput( this );

	PlayRankingMainOpenAni( true );
}

void UBWidget_RankingMain::OnClose()
{
	Super::OnClose();
}

void UBWidget_RankingMain::OnAnimationFinished_Implementation( const UWidgetAnimation* Animation )
{
	if( Animation != nullptr )
	{
		FName animName = Animation->GetMovieScene()->GetFName();
		if( animName == _Ani_RankingMainCloseName )
		{
			CloseUI();
		}
	}
}

void UBWidget_RankingMain::InitRankingMain()
{
	_SetSort( E_SORT_TYPE::E_SORT_TYPE_GOAL );

	_YearData.Empty();
	FString tmpYear;
	const TArray<FST_MATCH_DATA> matchDataList = UFBM_SaveGame::Get().GetMatchData_DB();
	for( int32 matchIndex = 0; matchIndex < matchDataList.Num(); ++matchIndex )
	{
		FString matchYear = matchDataList[matchIndex].MatchDate.Left( 4 );
		_YearData.AddUnique( matchYear );
		if( tmpYear.IsEmpty() || tmpYear < matchYear )
		{
			tmpYear = matchYear;
		}
	}

	_NowYear = tmpYear;
	_UpdateYear();

	_MainFilterItems.Empty();
	C_SB_RankingType->ClearChildren();
	C_SB_RankingType->ScrollToStart();

	// 랭킹 전체 타입
	UBWidget_EquipFilterItem* rankingAllWidget = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
	if( rankingAllWidget != nullptr )
	{
		rankingAllWidget->OwnerPannel = this;
		rankingAllWidget->SetEquipFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, 6 );
		if( rankingAllWidget->OnClickRankingFilter.IsBoundToObject( this ) == false )
		{
			rankingAllWidget->OnClickRankingFilter.AddUObject( this, &UBWidget_RankingMain::OnClickRankingMainFilter );
		}
		C_SB_RankingType->AddChild( rankingAllWidget );
		_MainFilterItems.Add( rankingAllWidget );
	}

	// 랭킹 A-Match 타입
	UBWidget_EquipFilterItem* rankingAMatchWidget = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
	if( rankingAMatchWidget != nullptr )
	{
		rankingAMatchWidget->OwnerPannel = this;
		rankingAMatchWidget->SetEquipFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_A_MATCH, 7 );
		if( rankingAMatchWidget->OnClickRankingFilter.IsBoundToObject( this ) == false )
		{
			rankingAMatchWidget->OnClickRankingFilter.AddUObject( this, &UBWidget_RankingMain::OnClickRankingMainFilter );
		}
		C_SB_RankingType->AddChild( rankingAMatchWidget );
		_MainFilterItems.Add( rankingAMatchWidget );
	}

	// 랭킹 자체전 타입
	UBWidget_EquipFilterItem* rankingOwnMatchWidget = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
	if( rankingOwnMatchWidget != nullptr )
	{
		rankingOwnMatchWidget->OwnerPannel = this;
		rankingOwnMatchWidget->SetEquipFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_OWN_MATCH, 8 );
		if( rankingOwnMatchWidget->OnClickRankingFilter.IsBoundToObject( this ) == false )
		{
			rankingOwnMatchWidget->OnClickRankingFilter.AddUObject( this, &UBWidget_RankingMain::OnClickRankingMainFilter );
		}
		C_SB_RankingType->AddChild( rankingOwnMatchWidget );
		_MainFilterItems.Add( rankingOwnMatchWidget );
	}

	OnClickRankingMainFilter( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
}

void UBWidget_RankingMain::UpdateTop3()
{
	BP_RankingTop3_Goal->Init();
	BP_RankingTop3_Goal->SetData(E_RANKING_TYPE::E_RANKING_TYPE_GOAL, _NowYear );

	BP_RankingTop3_Assist->Init();
	BP_RankingTop3_Assist->SetData( E_RANKING_TYPE::E_RANKING_TYPE_ASSIST, _NowYear );

	BP_RankingTop3_Point->Init();
	BP_RankingTop3_Point->SetData( E_RANKING_TYPE::E_RANKING_TYPE_POINT, _NowYear );

	BP_RankingTop3_Game->Init();
	BP_RankingTop3_Game->SetData( E_RANKING_TYPE::E_RANKING_TYPE_ATTENDANCE, _NowYear );
}

void UBWidget_RankingMain::SetSubRankingItem( const E_FILTER_ITEM_TYPE mainFilterType )
{
	C_SB_Item->ClearChildren();
	C_SB_Item->ScrollToStart();
	
	TArray<FST_PLAYER_DATA> playerDataList = UFBM_SaveGame::Get().GetPlayerData_DB();
	playerDataList.Sort( [mainFilterType, this]( const FST_PLAYER_DATA& A, const FST_PLAYER_DATA& B )
	{
		if( _SortType == E_SORT_TYPE::E_SORT_TYPE_GOAL )
		{
			if( A.GetNewGoalNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) > B.GetNewGoalNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
			{
				return true;
			}
			else if( A.GetNewGoalNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) == B.GetNewGoalNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
			{
				return A.GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) <= B.GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium );
			}
			else
			{
				return false;
			}
		}
		else if( _SortType == E_SORT_TYPE::E_SORT_TYPE_ASSIST )
		{
			if( A.GetNewAssistNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) > B.GetNewAssistNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
			{
				return true;
			}
			else if( A.GetNewAssistNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) == B.GetNewAssistNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
			{
				return A.GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) <= B.GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium );
			}
			else
			{
				return false;
			}
		}
		else if( _SortType == E_SORT_TYPE::E_SORT_TYPE_POINT )
		{
			if( A.GetNewPointNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) > B.GetNewPointNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
			{
				return true;
			}
			else if( A.GetNewPointNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) == B.GetNewPointNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
			{
				return A.GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) <= B.GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium );
			}
			else
			{
				return false;
			}
		}
		else if( _SortType == E_SORT_TYPE::E_SORT_TYPE_ATTENDANCE )
		{
			if( A.GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) >= B.GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		return false;
	} );

	int32 currentRank = 1;
	int32 plusIndex = 1;
	for( int32 playerIndex = 0; playerIndex < playerDataList.Num(); ++playerIndex )
	{
		UBWidget_RankingSlot* rankSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_RankingSlot>( EDynamicWidgetParts::RankingSlot );
		if( rankSlotWidget != nullptr )
		{
			if( _SortType == E_SORT_TYPE::E_SORT_TYPE_GOAL )
			{
				if( playerIndex == 0 )
				{
					currentRank = 1;
				}
				else
				{
					if( playerDataList[playerIndex-1].GetNewGoalNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) > playerDataList[playerIndex].GetNewGoalNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
					{
						currentRank += plusIndex;
						plusIndex = 1;
					}
					else if( playerDataList[playerIndex-1].GetNewGoalNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) == playerDataList[playerIndex].GetNewGoalNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
					{
						if (playerDataList[playerIndex-1].GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) == playerDataList[playerIndex].GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ))
						{
							plusIndex++;
						}
						else
						{
							currentRank += plusIndex;
							plusIndex = 1;
						}
					}
				}
			}
			else if( _SortType == E_SORT_TYPE::E_SORT_TYPE_ASSIST )
			{
				if( playerIndex == 0 )
				{
					currentRank = 1;
				}
				else
				{
					if( playerDataList[playerIndex - 1].GetNewAssistNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) > playerDataList[playerIndex].GetNewAssistNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
					{
						currentRank += plusIndex;
						plusIndex = 1;
					}
					else if( playerDataList[playerIndex - 1].GetNewAssistNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) == playerDataList[playerIndex].GetNewAssistNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
					{
						if( playerDataList[playerIndex - 1].GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) == playerDataList[playerIndex].GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
						{
							plusIndex++;
						}
						else
						{
							currentRank += plusIndex;
							plusIndex = 1;
						}
					}
				}
			}
			else if( _SortType == E_SORT_TYPE::E_SORT_TYPE_POINT )
			{
				if( playerIndex == 0 )
				{
					currentRank = 1;
				}
				else
				{
					if( playerDataList[playerIndex - 1].GetNewPointNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) > playerDataList[playerIndex].GetNewPointNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
					{
						currentRank += plusIndex;
						plusIndex = 1;
					}
					else if( playerDataList[playerIndex - 1].GetNewPointNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) == playerDataList[playerIndex].GetNewPointNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
					{
						if( playerDataList[playerIndex - 1].GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) == playerDataList[playerIndex].GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
						{
							plusIndex++;
						}
						else
						{
							currentRank += plusIndex;
							plusIndex = 1;
						}
					}
				}
			}
			else if( _SortType == E_SORT_TYPE::E_SORT_TYPE_ATTENDANCE )
			{
				if( playerIndex == 0 )
				{
					currentRank = 1;
				}
				else
				{
					if( playerDataList[playerIndex - 1].GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) > playerDataList[playerIndex].GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
					{
						currentRank += plusIndex;
						plusIndex = 1;
					}
					else if( playerDataList[playerIndex - 1].GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) == playerDataList[playerIndex].GetNewGamesNum( _NowYear, _RankingFilterInfo, mainFilterType, bIsExceptionStadium ) )
					{
						plusIndex++;
					}
				}
			}

			rankSlotWidget->OwnerPannel = this;
			rankSlotWidget->SetData( mainFilterType, _SortType, currentRank, playerDataList[playerIndex], _NowYear, _RankingFilterInfo, bIsExceptionStadium );
			C_SB_Item->AddChild( rankSlotWidget );
		}
	}
}

void UBWidget_RankingMain::PlayRankingMainOpenAni( const bool isOpen )
{
	if( isOpen )
	{
		if( _Ani_RankingMainOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_RankingMainOpen ) )
			{
				StopAnimation( _Ani_RankingMainOpen );
			}

			PlayAnimation( _Ani_RankingMainOpen );
		}
	}
	else
	{
		if( _Ani_RankingMainClose != nullptr )
		{
			if( IsAnimationPlaying( _Ani_RankingMainClose ) )
			{
				StopAnimation( _Ani_RankingMainClose );
			}

			PlayAnimation( _Ani_RankingMainClose );
		}
	}
}

void UBWidget_RankingMain::PlayFilterAni( bool isOpen )
{
	if( isOpen )
	{
		if( _Ani_FilterOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_FilterOpen ) )
			{
				StopAnimation( _Ani_FilterOpen );
			}

			PlayAnimation( _Ani_FilterOpen );
		}
	}
	else
	{
		if( Ani_FilterClose != nullptr )
		{
			if( IsAnimationPlaying( Ani_FilterClose ) )
			{
				StopAnimation( Ani_FilterClose );
			}

			PlayAnimation( Ani_FilterClose );
		}
	}
}

void UBWidget_RankingMain::ChangeSortType( const E_SORT_TYPE sortType )
{
	_OnClickRankingSortEvent( sortType );
}

void UBWidget_RankingMain::OnClickRankingMainFilter( const E_FILTER_ITEM_TYPE mainFilterType, bool isForce /*= true */ )
{
	if( isForce == false && _MainFilterType == mainFilterType )
	{
		return;
	}

	_MainFilterType = mainFilterType;

	switch( mainFilterType )
	{
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL:
		if( _MainFilterItems.IsValidIndex( 0 ) )
		{
			_MainFilterItems[0]->SelectEquipFilterItem( true );
		}
		if( _MainFilterItems.IsValidIndex( 1 ) )
		{
			_MainFilterItems[1]->SelectEquipFilterItem( false );
		}
		if( _MainFilterItems.IsValidIndex( 2 ) )
		{
			_MainFilterItems[2]->SelectEquipFilterItem( false );
		}
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_A_MATCH:
		if( _MainFilterItems.IsValidIndex( 0 ) )
		{
			_MainFilterItems[0]->SelectEquipFilterItem( false );
		}
		if( _MainFilterItems.IsValidIndex( 1 ) )
		{
			_MainFilterItems[1]->SelectEquipFilterItem( true );
		}
		if( _MainFilterItems.IsValidIndex( 2 ) )
		{
			_MainFilterItems[2]->SelectEquipFilterItem( false );
		}
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_OWN_MATCH:
		if( _MainFilterItems.IsValidIndex( 0 ) )
		{
			_MainFilterItems[0]->SelectEquipFilterItem( false );
		}
		if( _MainFilterItems.IsValidIndex( 1 ) )
		{
			_MainFilterItems[1]->SelectEquipFilterItem( false );
		}
		if( _MainFilterItems.IsValidIndex( 2 ) )
		{
			_MainFilterItems[2]->SelectEquipFilterItem( true );
		}
		break;
	}


	SetSubRankingItem( mainFilterType );
}

void UBWidget_RankingMain::_OnExceptionStadiumCheckStateChanged( bool isChecked )
{
	bIsExceptionStadium = isChecked;
	
	if( bIsExceptionStadium )
	{
		_RankingFilterInfo.CheckStadiumType( TEXT( "광주 문형 구장" ), false );
	}

	BP_RankingFilter_UMG->SetExceptionStadium( bIsExceptionStadium );
	SetSubRankingItem(_MainFilterType);
}

void UBWidget_RankingMain::_OnClick_ExceptionStadiumBtn()
{
	C_CB_ExceptionStadium->SetCheckedState( C_CB_ExceptionStadium->GetCheckedState() == ECheckBoxState::Checked ? ECheckBoxState::Unchecked : ECheckBoxState::Checked );
	_OnExceptionStadiumCheckStateChanged( C_CB_ExceptionStadium->GetCheckedState() == ECheckBoxState::Checked );
}

void UBWidget_RankingMain::_OnClick_SortBtn()
{
	BP_RankingSort_UMG->SetVisibility( ESlateVisibility::Visible );
	BP_RankingSort_UMG->InitRankingSort( _SortType );
}

void UBWidget_RankingMain::_OnClick_FilterBtn()
{
	BP_RankingFilter_UMG->SetVisibility( ESlateVisibility::Visible );
	BP_RankingFilter_UMG->OnShow();
	PlayFilterAni( true );
}

void UBWidget_RankingMain::_OnClickRankingSortEvent( const E_SORT_TYPE sortType )
{
	if( sortType != _SortType )
	{
		_SetSort( sortType );
		SetSubRankingItem( _MainFilterType );
	}

	BP_RankingSort_UMG->SetVisibility( ESlateVisibility::Collapsed );
}

void UBWidget_RankingMain::_OnClickRankingFilterApplyEvent( const FST_RANKING_FILTER_INFO curRankingFilterInfo )
{
	if ( BP_RankingFilter_UMG->GetVisibility() != ESlateVisibility::Collapsed )
	{
		PlayFilterAni( false );
	}
	
	BP_RankingFilter_UMG->SetVisibility( ESlateVisibility::Collapsed );

	_RankingFilterInfo = curRankingFilterInfo;

	_UpdateRankingFilter();
}

void UBWidget_RankingMain::_OnClickRankingFilterCancelEvent()
{
	PlayFilterAni( false );
	BP_RankingFilter_UMG->SetVisibility( ESlateVisibility::Collapsed );;
}

void UBWidget_RankingMain::_OnClick_YearPrevBtn()
{
	int32 nowYear = FCString::Atoi( *_NowYear );
	FString strPrevYear = FString::FromInt( nowYear - 1 );
	int32 findIndex = _YearData.Find( strPrevYear );
	if( findIndex != INDEX_NONE )
	{
		_NowYear = strPrevYear;
		_UpdateYear();
		SetSubRankingItem( _MainFilterType );
	}
}

void UBWidget_RankingMain::_OnClick_YearNextBtn()
{
	int32 nowYear = FCString::Atoi( *_NowYear );
	FString strNextYear = FString::FromInt( nowYear + 1 );
	int32 findIndex = _YearData.Find( strNextYear );
	if( findIndex != INDEX_NONE )
	{
		_NowYear = strNextYear;
		_UpdateYear();
		SetSubRankingItem( _MainFilterType );
	}
}

void UBWidget_RankingMain::_SetSort( const E_SORT_TYPE sortType )
{
	_SortType = sortType;

	C_Txt_Goal->SetColorAndOpacity( Color_StarBucksGrayFont );
	C_Txt_Assist->SetColorAndOpacity( Color_StarBucksGrayFont );
	C_Txt_Point->SetColorAndOpacity( Color_StarBucksGrayFont );
	C_Txt_Game->SetColorAndOpacity( Color_StarBucksGrayFont );

	switch( _SortType )
	{
	case E_SORT_TYPE::E_SORT_TYPE_GOAL:
		C_Txt_Sort->SetText( GET_BTEXT( 9 ) );
		C_Txt_Goal->SetColorAndOpacity( Color_RankBlue );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_ASSIST:
		C_Txt_Sort->SetText( GET_BTEXT( 10 ) );
		C_Txt_Assist->SetColorAndOpacity( Color_RankBlue );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_POINT:
		C_Txt_Sort->SetText( GET_BTEXT( 11 ) );
		C_Txt_Point->SetColorAndOpacity( Color_RankBlue );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_ATTENDANCE:
		C_Txt_Sort->SetText( GET_BTEXT( 32 ) );
		C_Txt_Game->SetColorAndOpacity( Color_RankBlue );
		break;
	default:
		break;
	}
}

void UBWidget_RankingMain::_UpdateYear()
{
	C_Txt_Year->SetText( FText::FromString( _NowYear ) );

	int32 nowYear = FCString::Atoi( *_NowYear );

	FString strPrevYear = FString::FromInt( nowYear - 1 );
	int32 findPrevIndex = _YearData.Find( strPrevYear );
	//C_Btn_Year_Prev->SetDisabled( findPrevIndex == INDEX_NONE ? true : false );

	FString strNextYear = FString::FromInt( nowYear + 1 );
	int32 findNextIndex = _YearData.Find( strNextYear );
	//C_Btn_Year_Next->SetDisabled( findNextIndex == INDEX_NONE ? true : false );

	UpdateTop3();

	BP_RankingFilter_UMG->SetYear( _NowYear );
}

void UBWidget_RankingMain::_UpdateRankingFilter()
{
	SetSubRankingItem(_MainFilterType);
}

bool UBWidget_RankingMain::_OnBackInput()
{
	if( BP_RankingSort_UMG->IsVisible() )
	{
		BP_RankingSort_UMG->SetVisibility( ESlateVisibility::Collapsed );
		return false;
	}
	else if( BP_RankingFilter_UMG->IsVisible() )
	{
		BP_RankingFilter_UMG->HandleBackInput();
		return false;
	}
	else
	{
		Super::_OnBackInput();
		PlayRankingMainOpenAni( false );
		return true;
	}
}

