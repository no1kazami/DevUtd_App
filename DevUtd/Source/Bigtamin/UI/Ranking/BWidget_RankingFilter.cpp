#include "BWidget_RankingFilter.h"
#include "BWidget_RankingMain.h"
#include "../Equip/BWidget_EquipBootsFilterItem.h"
#include "../../FBM_SaveGame.h"
#include "Bigtamin.h"

void UBWidget_RankingFilter::Init( UBWidget* OwnerUI )
{
	Super::Init( OwnerUI );

	ButtonDelegate_Clicked( this, C_Btn_Filter_Cancel, &UBWidget_RankingFilter::_OnClick_FilterCancel );
	ButtonDelegate_Clicked( this, C_Btn_Back, &UBWidget_RankingFilter::_OnClick_Back );
	ButtonDelegate_Clicked( this, C_Btn_Apply, &UBWidget_RankingFilter::_OnClick_Apply );
	ButtonDelegate_Clicked( this, C_Btn_Reset, &UBWidget_RankingFilter::_OnClick_Reset );

	ButtonDelegate_Clicked( this, C_Btn_Ground, &UBWidget_RankingFilter::_OnClick_Stadium );
	ButtonDelegate_Clicked( this, C_Btn_AwayTeam, &UBWidget_RankingFilter::_OnClick_AwayTeam );
	ButtonDelegate_Clicked( this, C_Btn_Month, &UBWidget_RankingFilter::_OnClick_Month );

	C_CB_Ground->OnCheckStateChanged.RemoveDynamic( this, &UBWidget_RankingFilter::_OnGroundCheckStateChanged );
	C_CB_Ground->OnCheckStateChanged.AddDynamic( this, &UBWidget_RankingFilter::_OnGroundCheckStateChanged );
	C_CB_AwayTeam->OnCheckStateChanged.RemoveDynamic( this, &UBWidget_RankingFilter::_OnAwayTeamCheckStateChanged );
	C_CB_AwayTeam->OnCheckStateChanged.AddDynamic( this, &UBWidget_RankingFilter::_OnAwayTeamCheckStateChanged );
	C_CB_Month->OnCheckStateChanged.RemoveDynamic( this, &UBWidget_RankingFilter::_OnMonthCheckStateChanged );
	C_CB_Month->OnCheckStateChanged.AddDynamic( this, &UBWidget_RankingFilter::_OnMonthCheckStateChanged );

	_InitRankingFilter();
}

void UBWidget_RankingFilter::ResetFilter()
{
	// 구장 Reset
	for( int i = 0; i < C_VB_Filter_Ground->GetChildrenCount(); i++ )
	{
		UBWidget_EquipBootsFilterItem* It = Cast<UBWidget_EquipBootsFilterItem>( C_VB_Filter_Ground->GetChildAt( i ) );
		if( It != nullptr )
		{
			It->ResetFilterItem();
		}
	}

	C_CB_Ground->SetCheckedState( ECheckBoxState::Unchecked );
	_OnGroundCheckStateChanged( false );

	// 상대팀 Reset
	for( int i = 0; i < C_VB_Filter_AwayTeam->GetChildrenCount(); i++ )
	{
		UBWidget_EquipBootsFilterItem* It = Cast<UBWidget_EquipBootsFilterItem>( C_VB_Filter_AwayTeam->GetChildAt( i ) );
		if( It != nullptr )
		{
			It->ResetFilterItem();
		}
	}

	C_CB_AwayTeam->SetCheckedState( ECheckBoxState::Unchecked );
	_OnAwayTeamCheckStateChanged( false );

	// 기간 Reset
	for( int i = 0; i < C_VB_Filter_Month->GetChildrenCount(); i++ )
	{
		UBWidget_EquipBootsFilterItem* It = Cast<UBWidget_EquipBootsFilterItem>( C_VB_Filter_Month->GetChildAt( i ) );
		if( It != nullptr )
		{
			It->ResetFilterItem();
		}
	}

	C_CB_Month->SetCheckedState( ECheckBoxState::Unchecked );
	_OnMonthCheckStateChanged( false );

	// 필터 Reset
	_FilterInfo.InitFilterInfo();
	_PrevFilterInfo.InitFilterInfo();

	_InitRankingFilter();
}

void UBWidget_RankingFilter::ResetFilter( E_BRAND_TYPE brandType )
{
	ResetFilter();

	C_Ol_Ground->SetVisibility( (brandType == E_BRAND_TYPE::E_BRAND_TYPE_ALL) ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed );
}

void UBWidget_RankingFilter::HandleBackInput()
{
	_OnClick_Back();
}

void UBWidget_RankingFilter::SetYear( FString InYear )
{
	_CurYear = InYear;
}

void UBWidget_RankingFilter::SetExceptionStadium( bool isExceptionStadium )
{
	bIsExceptionStadium = isExceptionStadium;
	//_OnClick_Reset();

	if ( bIsExceptionStadium )
	{
		_FilterInfo.CheckStadiumType( TEXT( "광주 문형 구장" ), false );
		_PrevFilterInfo.CheckStadiumType( TEXT( "광주 문형 구장" ), false );
	}
}

void UBWidget_RankingFilter::OnClose()
{
	Super::OnClose();
}

void UBWidget_RankingFilter::OnShow()
{
	_UpdateEquipBootsFilter( E_BOOTS_FILTER_TYPE::MAX );

	C_CB_Ground->SetCheckedState( ECheckBoxState::Unchecked );
	_OnGroundCheckStateChanged( false );
	C_CB_AwayTeam->SetCheckedState( ECheckBoxState::Unchecked );
	_OnAwayTeamCheckStateChanged( false );
	C_CB_Month->SetCheckedState( ECheckBoxState::Unchecked );
	_OnMonthCheckStateChanged( false );
}

void UBWidget_RankingFilter::_OnClick_FilterCancel()
{
	OnClickRankingFilterCancel.Broadcast();
}

void UBWidget_RankingFilter::_OnClick_Back()
{
	_FilterInfo = _PrevFilterInfo;
	OnClickRankingFilterCancel.Broadcast();
}

void UBWidget_RankingFilter::_OnClick_Apply()
{
	_PrevFilterInfo = _FilterInfo;
	OnClickRankingFilterApply.Broadcast( _FilterInfo );
}

void UBWidget_RankingFilter::_OnClick_Reset()
{
	ResetFilter();
	_OnClick_Apply();
}

void UBWidget_RankingFilter::_ResetClick( E_BOOTS_FILTER_TYPE clickFilterType )
{
	C_SB_Filter->ScrollToStart();

	if( clickFilterType != E_BOOTS_FILTER_TYPE::STADIUM )
	{
		C_CB_Ground->SetCheckedState( ECheckBoxState::Unchecked );
		_OnGroundCheckStateChanged( false );
	}
	if( clickFilterType != E_BOOTS_FILTER_TYPE::AWAY_TEAM )
	{
		C_CB_AwayTeam->SetCheckedState( ECheckBoxState::Unchecked );
		_OnAwayTeamCheckStateChanged( false );
	}
	if( clickFilterType != E_BOOTS_FILTER_TYPE::MONTH )
	{
		C_CB_Month->SetCheckedState( ECheckBoxState::Unchecked );
		_OnMonthCheckStateChanged( false );
	}
}

void UBWidget_RankingFilter::_OnClick_Stadium()
{
	_ResetClick( E_BOOTS_FILTER_TYPE::STADIUM );

	C_CB_Ground->SetCheckedState( C_CB_Ground->GetCheckedState() == ECheckBoxState::Checked ? ECheckBoxState::Unchecked : ECheckBoxState::Checked );
	_OnGroundCheckStateChanged( C_CB_Ground->GetCheckedState() == ECheckBoxState::Checked );
}

void UBWidget_RankingFilter::_OnClick_AwayTeam()
{
	_ResetClick( E_BOOTS_FILTER_TYPE::AWAY_TEAM );

	C_CB_AwayTeam->SetCheckedState( C_CB_AwayTeam->GetCheckedState() == ECheckBoxState::Checked ? ECheckBoxState::Unchecked : ECheckBoxState::Checked );
	_OnAwayTeamCheckStateChanged( C_CB_AwayTeam->GetCheckedState() == ECheckBoxState::Checked );
}

void UBWidget_RankingFilter::_OnClick_Month()
{
	_ResetClick( E_BOOTS_FILTER_TYPE::MONTH );

	C_CB_Month->SetCheckedState( C_CB_Month->GetCheckedState() == ECheckBoxState::Checked ? ECheckBoxState::Unchecked : ECheckBoxState::Checked );
	_OnMonthCheckStateChanged( C_CB_Month->GetCheckedState() == ECheckBoxState::Checked );
}

void UBWidget_RankingFilter::_OnGroundCheckStateChanged( bool isChecked )
{
	C_VB_Filter_Ground->SetVisibility( isChecked ? ESlateVisibility::Visible : ESlateVisibility::Collapsed );
	C_Img_LineGround->SetVisibility( isChecked ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
}

void UBWidget_RankingFilter::_OnAwayTeamCheckStateChanged( bool isChecked )
{
	C_VB_Filter_AwayTeam->SetVisibility( isChecked ? ESlateVisibility::Visible : ESlateVisibility::Collapsed );
	C_Img_LineAwayTeam->SetVisibility( isChecked ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
}

void UBWidget_RankingFilter::_OnMonthCheckStateChanged( bool isChecked )
{
	C_VB_Filter_Month->SetVisibility( isChecked ? ESlateVisibility::Visible : ESlateVisibility::Collapsed );
	C_Img_LineMonth->SetVisibility( isChecked ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
}

void UBWidget_RankingFilter::_HandleStadiumFilter( const FString stadiumType, const bool isCheck )
{
	_FilterInfo.CheckStadiumType( stadiumType, isCheck );
	_UpdateEquipBootsFilter( E_BOOTS_FILTER_TYPE::STADIUM );
}

void UBWidget_RankingFilter::_HandleAwayTeamFilter( const FString AwayTeamType, const bool isCheck )
{
	_FilterInfo.CheckAwayTeamType( AwayTeamType, isCheck );
	_UpdateEquipBootsFilter( E_BOOTS_FILTER_TYPE::AWAY_TEAM );
}

void UBWidget_RankingFilter::_HandleMonthFilter( const int32 MonthType, const bool isCheck )
{
	_FilterInfo.CheckMonthType( MonthType, isCheck );
	_UpdateEquipBootsFilter( E_BOOTS_FILTER_TYPE::MONTH );
}

void UBWidget_RankingFilter::_InitRankingFilter()
{
	TArray<FString> stadiumInfo;
	TArray<FString> teamInfo;
	TArray<int32> monthInfo;
	_GetFilteringCategoryData( stadiumInfo, teamInfo, monthInfo );

	// 구장 초기화
	_ResetFilter_Stadium( stadiumInfo );

	// 상대팀 초기화
	_ResetFilter_AwayTeam( teamInfo );

	// 기간 초기화
	_ResetFilter_Month( monthInfo );
}

void UBWidget_RankingFilter::_UpdateEquipBootsFilter( E_BOOTS_FILTER_TYPE filterType )
{
	TArray<FString> stadiumInfo;
	TArray<FString> teamInfo;
	TArray<int32> monthInfo;
	_GetFilteringCategoryData( stadiumInfo, teamInfo, monthInfo );

	// 구장 필터 업데이트
	_ResetFilter_Stadium( stadiumInfo );

	// 상대팀 필터 업데이트
	_ResetFilter_AwayTeam( teamInfo );

	// 기간 필터 업데이트
	_ResetFilter_Month( monthInfo );
}

void UBWidget_RankingFilter::_GetFilteringCategoryData( TArray<FString>& Out_StadiumInfo, TArray<FString>& Out_TeamInfo, TArray<int32>& Out_MonthInfo )
{
	// 필터링된 데이터 가져오기
	E_SORT_TYPE curSortType = E_SORT_TYPE::E_SORT_TYPE_NONE;
	_GetFilterType( curSortType );

	FST_RANKING_FILTER_INFO tempFilterInfo = _FilterInfo;

#if DB_BOOTS_DATA
	// 필터링 Data 없을때
	if( tempFilterInfo.IsNotFilter() )
	{
		TArray<FST_STADIUM_INFO_DATA> stadiumDataList = UFBM_SaveGame::Get().GetStadiumData_DB();
		for( auto& stadiumData : stadiumDataList )
		{
			Out_StadiumInfo.AddUnique( stadiumData.StadiumName );
		}

		TArray<FST_TEAM_INFO_DATA> teamDataList = UFBM_SaveGame::Get().GetTeamData_DB();
		for( auto& teamData : teamDataList )
		{
			Out_TeamInfo.AddUnique( teamData.TeamName );
		}

		Out_MonthInfo.AddUnique( 1 );
		Out_MonthInfo.AddUnique( 2 );
		Out_MonthInfo.AddUnique( 3 );
		Out_MonthInfo.AddUnique( 4 );
		Out_MonthInfo.AddUnique( 5 );
		Out_MonthInfo.AddUnique( 6 );
		Out_MonthInfo.AddUnique( 7 );
		Out_MonthInfo.AddUnique( 8 );
		Out_MonthInfo.AddUnique( 9 );
		Out_MonthInfo.AddUnique( 10 );
		Out_MonthInfo.AddUnique( 11 );
		Out_MonthInfo.AddUnique( 12 );

		return;
	}

	// 구장 카테고리 필터링
	if( tempFilterInfo.StadiumTypes.Num() > 0 )
	{
		TArray<FST_STADIUM_INFO_DATA> stadiumDataList = UFBM_SaveGame::Get().GetStadiumData_DB();
		for( auto& stadiumData : stadiumDataList )
		{
			for( auto& stadiumType : tempFilterInfo.StadiumTypes )
			{
				if( stadiumData.StadiumName == stadiumType )
				{
					Out_StadiumInfo.AddUnique( stadiumType );
					break;
				}
			}
		}
	}

	// 상대팀 카테고리 필터링
	if( tempFilterInfo.AwayTeamTypes.Num() > 0 )
	{
		TArray<FST_TEAM_INFO_DATA> teamDataList = UFBM_SaveGame::Get().GetTeamData_DB();
		for( auto& teamData : teamDataList )
		{
			for( auto& awayTeamType : tempFilterInfo.AwayTeamTypes )
			{
				if( teamData.TeamName == awayTeamType )
				{
					Out_TeamInfo.AddUnique( awayTeamType );
					break;
				}
			}
		}
	}

	// 기간 카테고리 필터링
	if( tempFilterInfo.MonthTypes.Num() > 0 )
	{
		TArray<FST_MATCH_DATA> matchDataList = UFBM_SaveGame::Get().GetMatchData_DB();
		for( auto& matchData : matchDataList )
		{
			if( matchData.InfoType == E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE )
			{
				continue;
			}

			FString MatchDate = matchData.MatchDate;
			FString strYear = MatchDate.Left( 4 );
			if ( _CurYear != strYear )
			{
				continue;
			}

			FString strMon = MatchDate.Mid( 4, 2 );
			int32 tempMonth = FCString::Atoi( *strMon );

			for( auto& monthType : tempFilterInfo.MonthTypes )
			{
				if( tempMonth == monthType )
				{
					Out_MonthInfo.AddUnique( monthType );
					break;
				}
			}
		}
	}
#else
#endif
}

void UBWidget_RankingFilter::_GetFilterType( E_SORT_TYPE& Out_SortType )
{
	Out_SortType = E_SORT_TYPE::E_SORT_TYPE_NONE;
	if( this->OwnerPannel != nullptr )
	{
		if( UBWidget_RankingMain* ownerRankingMain = Cast<UBWidget_RankingMain>( this->OwnerPannel ) )
		{
			Out_SortType = ownerRankingMain->GetSortType();
		}
	}
}

void UBWidget_RankingFilter::_ResetFilter_Stadium( const TArray<FString>& stadiumInfo )
{
	C_Txt_Count_Ground->SetVisibility( _FilterInfo.StadiumTypes.Num() > 0 ? ESlateVisibility::Visible : ESlateVisibility::Hidden );
	if( _FilterInfo.StadiumTypes.Num() > 0 )
	{
		FText mainText = FText::FromString( _FilterInfo.StadiumTypes[0] );
		if( _FilterInfo.StadiumTypes.Num() == 1 )
		{
			C_Txt_Count_Ground->SetText( mainText );
		}
		else
		{
			C_Txt_Count_Ground->SetText( FText::Format( GET_BTEXT( 58 ), mainText, FText::AsNumber( _FilterInfo.StadiumTypes.Num() - 1 ) ) );
		}
	}

	TMap< FString, FiterDataInfo> mapStadium;
	TArray<FST_STADIUM_INFO_DATA> stadiumDataList = UFBM_SaveGame::Get().GetStadiumData_DB();
	for( auto& stadiumData : stadiumDataList )
	{
		if( bIsExceptionStadium && stadiumData.StadiumName == TEXT( "광주 문형 구장" ) )
		{
			continue;
		}

		bool bIsFind = false;
		for( auto& checkStadium : _FilterInfo.StadiumTypes )
		{
			if( checkStadium == stadiumData.StadiumName )
			{
				bIsFind = true;
				break;
			}
		}

		mapStadium.Add( stadiumData.StadiumName, FiterDataInfo( bIsFind ) );
	}

	mapStadium.KeySort( []( FString A, FString B )
					  {
						  return A < B;
					  } );

	// 필터링된 데이터에서 해당 경기장 계산
	for( auto& stadium : mapStadium )
	{
		int32 stadiumCount = 0;
		const TArray<FST_MATCH_DATA> matchDataList = UFBM_SaveGame::Get().GetMatchData_DB();
		for( auto& matchData : matchDataList )
		{
			if ( matchData.InfoType == E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE)
			{
				continue;
			}

			FString strYear = matchData.MatchDate.Left( 4 );
			FString strMon = matchData.MatchDate.Mid( 4, 2 );
			int32 tempMonth = FCString::Atoi( *strMon );
			if( stadium.Key == matchData.Comment && _CurYear == strYear )
			{
				if( _FilterInfo.AwayTeamTypes.Num() == 0 && _FilterInfo.MonthTypes.Num() == 0 )
				{
					stadiumCount++;
				}
				else
				{
					// 상대팀, 기간 필터링
					if ( _FilterInfo.AwayTeamTypes.Num() > 0 && _FilterInfo.MonthTypes.Num() == 0 )
					{
						for( auto& checkTeam : _FilterInfo.AwayTeamTypes )
						{
							if( checkTeam == matchData.AwayTeamName )
							{
								stadiumCount++;
								break;
							}
						}
					}
					else if( _FilterInfo.MonthTypes.Num() > 0 && _FilterInfo.AwayTeamTypes.Num() == 0 )
					{
						for( auto& checkMonth : _FilterInfo.MonthTypes )
						{
							if( checkMonth == tempMonth )
							{
								stadiumCount++;
								break;
							}
						}
					}
					else
					{
						for( auto& checkTeam : _FilterInfo.AwayTeamTypes )
						{
							bool bIsSuccess = false;
							if( checkTeam == matchData.AwayTeamName )
							{
								for( auto& checkMonth : _FilterInfo.MonthTypes )
								{
									if( checkMonth == tempMonth )
									{
										stadiumCount++;
										bIsSuccess = true;
										break;
									}
								}

								if( bIsSuccess )
								{
									break;
								}
							}
						}
					}
				}
			}
		}

		stadium.Value.dataCount = stadiumCount;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	C_VB_Filter_Ground->ClearChildren();

	for( auto& stadium : mapStadium )
	{
		UBWidget_EquipBootsFilterItem* bootsFilterItem = B_HUD->CreateDynamicWidget<UBWidget_EquipBootsFilterItem>( EDynamicWidgetParts::EquipBootsFilterItem );
		if( bootsFilterItem != nullptr )
		{
			bootsFilterItem->OwnerPannel = this;
			bootsFilterItem->SetRankingFilterData_Stadium( stadium.Key, stadium.Value.isChecked, stadium.Value.dataCount );
			if( bootsFilterItem->OnClickFilterStadium.IsBoundToObject( this ) == false )
			{
				bootsFilterItem->OnClickFilterStadium.AddUObject( this, &UBWidget_RankingFilter::_HandleStadiumFilter );
			}

			C_VB_Filter_Ground->AddChild( bootsFilterItem );
		}
	}
}

void UBWidget_RankingFilter::_ResetFilter_AwayTeam( const TArray<FString>& teamInfo )
{
	C_Txt_Count_AwayTeam->SetVisibility( _FilterInfo.AwayTeamTypes.Num() > 0 ? ESlateVisibility::Visible : ESlateVisibility::Hidden );
	if( _FilterInfo.AwayTeamTypes.Num() > 0 )
	{
		FText mainText = FText::FromString( _FilterInfo.AwayTeamTypes[0] );
		if( _FilterInfo.AwayTeamTypes.Num() == 1 )
		{
			C_Txt_Count_AwayTeam->SetText( mainText );
		}
		else
		{
			C_Txt_Count_AwayTeam->SetText( FText::Format( GET_BTEXT( 58 ), mainText, FText::AsNumber( _FilterInfo.AwayTeamTypes.Num() - 1 ) ) );
		}
	}

	TMap< FString, FiterDataInfo> mapAwayTeam;
	TArray<FST_TEAM_INFO_DATA> teamDataList = UFBM_SaveGame::Get().GetTeamData_DB();
	for( auto& teamData : teamDataList )
	{
		bool bIsFind = false;
		for( auto& checkTeam : _FilterInfo.AwayTeamTypes )
		{
			if( checkTeam == teamData.TeamName )
			{
				bIsFind = true;
				break;
			}
		}

		mapAwayTeam.Add( teamData.TeamName, FiterDataInfo( bIsFind ) );
	}

	mapAwayTeam.KeySort( []( FString A, FString B )
						 {
							 return A < B;
						 } );

	// 필터링된 데이터에서 해당 경기장 갯수 계산
	for( auto& team : mapAwayTeam )
	{
		int32 teamCount = 0;
		const TArray<FST_MATCH_DATA> matchDataList = UFBM_SaveGame::Get().GetMatchData_DB();
		for( auto& matchData : matchDataList )
		{
			if( matchData.InfoType == E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE )
			{
				continue;
			}

			FString strYear = matchData.MatchDate.Left( 4 );
			FString strMon = matchData.MatchDate.Mid( 4, 2 );
			int32 tempMonth = FCString::Atoi( *strMon );
			if( team.Key == matchData.AwayTeamName && _CurYear == strYear )
			{
				if( bIsExceptionStadium && matchData.Comment == TEXT( "광주 문형 구장" ) )
				{
					continue;
				}

				if( _FilterInfo.StadiumTypes.Num() == 0 && _FilterInfo.MonthTypes.Num() == 0 )
				{
					teamCount++;
				}
				else
				{
					// 상대팀, 기간 필터링
					if( _FilterInfo.StadiumTypes.Num() > 0 && _FilterInfo.MonthTypes.Num() == 0 )
					{
						for( auto& checkStadium : _FilterInfo.StadiumTypes )
						{
							if( checkStadium == matchData.Comment )
							{
								teamCount++;
								break;
							}
						}
					}
					else if( _FilterInfo.MonthTypes.Num() > 0 && _FilterInfo.StadiumTypes.Num() == 0 )
					{
						for( auto& checkMonth : _FilterInfo.MonthTypes )
						{
							if( checkMonth == tempMonth )
							{
								teamCount++;
								break;
							}
						}
					}
					else
					{
						for( auto& checkStadium : _FilterInfo.StadiumTypes )
						{
							bool bIsSuccess = false;
							if( checkStadium == matchData.Comment )
							{
								for( auto& checkMonth : _FilterInfo.MonthTypes )
								{
									if( checkMonth == tempMonth )
									{
										teamCount++;
										bIsSuccess = true;
										break;
									}
								}

								if ( bIsSuccess )
								{
									break;
								}
							}
						}
					}
				}
			}
		}

		team.Value.dataCount = teamCount;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	C_VB_Filter_AwayTeam->ClearChildren();

	for( auto& team : mapAwayTeam )
	{
		UBWidget_EquipBootsFilterItem* bootsFilterItem = B_HUD->CreateDynamicWidget<UBWidget_EquipBootsFilterItem>( EDynamicWidgetParts::EquipBootsFilterItem );
		if( bootsFilterItem != nullptr )
		{
			bootsFilterItem->OwnerPannel = this;
			bootsFilterItem->SetRankingFilterData_Team( team.Key, team.Value.isChecked, team.Value.dataCount );
			if( bootsFilterItem->OnClickFilterTeam.IsBoundToObject( this ) == false )
			{
				bootsFilterItem->OnClickFilterTeam.AddUObject( this, &UBWidget_RankingFilter::_HandleAwayTeamFilter );
			}

			C_VB_Filter_AwayTeam->AddChild( bootsFilterItem );
		}
	}
}

void UBWidget_RankingFilter::_ResetFilter_Month( const TArray<int32>& monthInfo )
{
	C_Txt_Count_Month->SetVisibility( _FilterInfo.MonthTypes.Num() > 0 ? ESlateVisibility::Visible : ESlateVisibility::Hidden );
	if( _FilterInfo.MonthTypes.Num() > 0 )
	{
		FText mainText = FText::AsNumber( _FilterInfo.MonthTypes[0] );
		if( _FilterInfo.MonthTypes.Num() == 1 )
		{
			C_Txt_Count_Month->SetText( mainText );
		}
		else
		{
			C_Txt_Count_Month->SetText( FText::Format( GET_BTEXT( 58 ), mainText, FText::AsNumber( _FilterInfo.MonthTypes.Num() - 1 ) ) );
		}
	}

	TMap< int32, FiterDataInfo> mapMonth;
	for( int32 index = 1; index <= 12; ++index )
	{
		bool bIsFind = false;
		for( auto& checkMonth : _FilterInfo.MonthTypes )
		{
			if( checkMonth == index )
			{
				bIsFind = true;
				break;
			}
		}

		mapMonth.Add( index, FiterDataInfo( bIsFind ) );
	}

	mapMonth.KeySort( []( int32 A, int32 B )
						 {
							 return A < B;
						 } );

	// 필터링된 데이터에서 해당 기간 갯수 계산
	for( auto& month : mapMonth )
	{
		int32 monthCount = 0;
		const TArray<FST_MATCH_DATA> matchDataList = UFBM_SaveGame::Get().GetMatchData_DB();
		for( auto& matchData : matchDataList )
		{
			if( matchData.InfoType == E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE )
			{
				continue;
			}

			FString strYear = matchData.MatchDate.Left( 4 );
			FString strMon = matchData.MatchDate.Mid( 4, 2 );
			int32 tempMonth = FCString::Atoi( *strMon );
			if( month.Key == tempMonth && _CurYear == strYear )
			{
				if( bIsExceptionStadium && matchData.Comment == TEXT( "광주 문형 구장" ) )
				{
					continue;
				}

				if( _FilterInfo.StadiumTypes.Num() == 0 && _FilterInfo.AwayTeamTypes.Num() == 0 )
				{
					monthCount++;
				}
				else
				{
					// 상대팀, 구장 필터링
					if( _FilterInfo.StadiumTypes.Num() > 0 && _FilterInfo.AwayTeamTypes.Num() == 0 )
					{
						for( auto& checkStadium : _FilterInfo.StadiumTypes )
						{
							if( checkStadium == matchData.Comment )
							{
								monthCount++;
								break;
							}
						}
					}
					else if( _FilterInfo.AwayTeamTypes.Num() > 0 && _FilterInfo.StadiumTypes.Num() == 0 )
					{
						for( auto& checkTeam : _FilterInfo.AwayTeamTypes )
						{
							if( checkTeam == matchData.AwayTeamName )
							{
								monthCount++;
								break;
							}
						}
					}
					else
					{
						for( auto& checkStadium : _FilterInfo.StadiumTypes )
						{
							bool bIsSuccess = false;
							if( checkStadium == matchData.Comment )
							{
								for( auto& checkTeam : _FilterInfo.AwayTeamTypes )
								{
									if( checkTeam == matchData.AwayTeamName )
									{
										monthCount++;
										bIsSuccess = true;
										break;
									}
								}

								if( bIsSuccess )
								{
									break;
								}
							}
						}
					}
				}
			}
		}

		month.Value.dataCount = monthCount;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	C_VB_Filter_Month->ClearChildren();

	for( auto& month : mapMonth )
	{
		UBWidget_EquipBootsFilterItem* bootsFilterItem = B_HUD->CreateDynamicWidget<UBWidget_EquipBootsFilterItem>( EDynamicWidgetParts::EquipBootsFilterItem );
		if( bootsFilterItem != nullptr )
		{
			bootsFilterItem->OwnerPannel = this;
			bootsFilterItem->SetRankingFilterData_Month( month.Key, month.Value.isChecked, month.Value.dataCount );
			if( bootsFilterItem->OnClickFilterMonth.IsBoundToObject( this ) == false )
			{
				bootsFilterItem->OnClickFilterMonth.AddUObject( this, &UBWidget_RankingFilter::_HandleMonthFilter );
			}

			C_VB_Filter_Month->AddChild( bootsFilterItem );
		}
	}
}
