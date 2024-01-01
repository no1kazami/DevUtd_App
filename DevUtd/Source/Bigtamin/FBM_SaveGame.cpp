// Fill out your copyright notice in the Description page of Project Settings.

#include "FBM_SaveGame.h"
#include "Bigtamin.h"
#include "Kismet/KismetStringLibrary.h"

UFBM_SaveGame::UFBM_SaveGame()
{

}

UFBM_SaveGame& UFBM_SaveGame::Get()
{
// #if PLATFORM_ANDROID
// 	return *(GInst->DevUtdSaveGame);
// #else
	static UFBM_SaveGame* s_save = nullptr;
	if( s_save != nullptr && s_save->_SlotName != _GetSlotName() )
	{
		s_save = nullptr;
	}

	if( s_save == nullptr )
	{
		s_save = Cast<UFBM_SaveGame>( UGameplayStatics::LoadGameFromSlot( _GetSlotName(), 0 ) );

		if( s_save == nullptr )
		{
			s_save = Cast<UFBM_SaveGame>( UGameplayStatics::CreateSaveGameObject( UFBM_SaveGame::StaticClass() ) );
		}
		s_save->AddToRoot();
		s_save->_SlotName = _GetSlotName();

#if PLATFORM_WINDOWS
		s_save->_SetData_Windows();
#endif

		FBM_LOG_FUNCTION_INFO( Log, TEXT( "Save Game Created" ) );
	}

	ensure( s_save != nullptr );
	return *s_save;
/*#endif*/
}

void UFBM_SaveGame::SaveFile()
{
	UGameplayStatics::SaveGameToSlot( &Get(), _GetSlotName(), 0 );
}

bool UFBM_SaveGame::IsTodayFirstLogin( bool isNowSave /*= false */)
{
	if( _LoginDate.Compare( FDateTime::Today().ToString() ) == 0 )
	{
		return false;
	}

	_LoginDate = FDateTime::Today().ToString();

	if( isNowSave )
	{
		SaveFile();
	}

	return true;
}

void UFBM_SaveGame::SetCurVersion( FString configData, bool isNowSave /*= false */ )
{
	_CurVersion = configData;

	if( isNowSave )
	{
		SaveFile();
	}
}

void UFBM_SaveGame::SetServetCheckTime( FString configData, bool isNowSave /*= false */ )
{
	_ServetCheckTime = configData;

	if( isNowSave )
	{
		SaveFile();
	}
}

void UFBM_SaveGame::SetScrollClickSensitivity( int32 configData, bool isNowSave /*= false */ )
{
	_ScrollClickSensitivity = configData;

	if( isNowSave )
	{
		SaveFile();
	}
}

void UFBM_SaveGame::SetMainBrand( FString configData, bool isNowSave /*= false */ )
{
	_MainBrand = configData;

	if( isNowSave )
	{
		SaveFile();
	}
}

void UFBM_SaveGame::SetMainCustomMenu( TArray<FString> configData, bool isNowSave /*= false */ )
{
	_MainCustomMenu = configData;

	if( isNowSave )
	{
		SaveFile();
	}
}

void UFBM_SaveGame::SetReviewURL( FString configData, bool isNowSave /*= false */ )
{
	_ReviewUrl = configData;

	if( isNowSave )
	{
		SaveFile();
	}
}

FString UFBM_SaveGame::GetReviewURL() const
{
	return _ReviewUrl;
}

void UFBM_SaveGame::SetRuleURL( FString configData, bool isNowSave /*= false */ )
{
	_RuleUrl = configData;

	if( isNowSave )
	{
		SaveFile();
	}
}

FString UFBM_SaveGame::GetRuleURL() const
{
	return _RuleUrl;
}

void UFBM_SaveGame::SetSendEmailAddress( FString configData, bool isNowSave /*= false */ )
{
	//FBM_LOG_FUNCTION_INFO( Log, TEXT( "SetSendEmailAddress [ %s ] " ), *configData );

	_SendEmailAddress = configData;

	if( isNowSave )
	{
		SaveFile();
	}
}

FString UFBM_SaveGame::GetSendEmailAddress() const
{
	return _SendEmailAddress;
}

void UFBM_SaveGame::SetShareAppAddress( FString configData, bool isNowSave /*= false */ )
{
	//FBM_LOG_FUNCTION_INFO( Log, TEXT( "SetShareAppAddress [ %s ] " ), *configData );

	_ShareAppAddress = configData;

	if( isNowSave )
	{
		SaveFile();
	}
}

FString UFBM_SaveGame::GetShareAppAddress() const
{
	return _ShareAppAddress;
}

void UFBM_SaveGame::SetShowSupport( int32 configData, bool isNowSave /*= false */ )
{
	_IsShowSupport = configData;

	if( isNowSave )
	{
		SaveFile();
	}
}

bool UFBM_SaveGame::IsShowSupport() const
{
	return _IsShowSupport > 0;
}

void UFBM_SaveGame::SetShowPartnership( int32 configData, bool isNowSave /*= false */ )
{
	_IsShowPartnership = configData;

	if( isNowSave )
	{
		SaveFile();
	}
}

bool UFBM_SaveGame::IsShowPartnership() const
{
	return _IsShowPartnership > 0;
}

void UFBM_SaveGame::SetNewBootsMaxCount( int32 configData, bool isNowSave /*= false */ )
{
	_NewBootsMaxCount = configData;

	if( isNowSave )
	{
		SaveFile();
	}
}

int32 UFBM_SaveGame::GetNewBootsMaxCount() const
{
	return _NewBootsMaxCount;
}

// (0 : 모두 오픈, 1 : 제품 정보만 오픈, 2 : 제품 정보, 리뷰 오픈, 3 : 제품 정보, 구매하기 오픈)
void UFBM_SaveGame::SetShowBootsDetail( int32 configData, bool isNowSave /*= false */ )
{
	_ShowBootsDetail = configData;

	if( isNowSave )
	{
		SaveFile();
	}
}

int32 UFBM_SaveGame::GetShowBootsDetail() const
{
	return _ShowBootsDetail;
}

FString UFBM_SaveGame::GetCurVersion() const
{
	return _CurVersion;
}

FString UFBM_SaveGame::GetServetCheckTime() const
{
	return _ServetCheckTime;
}

int32 UFBM_SaveGame::GetScrollClickSensitivity() const
{
	return _ScrollClickSensitivity;
}

FString UFBM_SaveGame::GetMainBrand() const
{
	return _MainBrand;
}

TArray<FString> UFBM_SaveGame::GetMainCustomMenu() const
{
	return _MainCustomMenu;
}

const FST_BOOTS_CRAWLING_DATA* UFBM_SaveGame::GetBootsCrawlingData( FString bootsProductID )
{
	if (_FIreBaseCrawlingDBVersion <= 0)
	{
		return nullptr;
	}

	bool isModify = false;
	FST_BOOTS_CRAWLING_DATA* crawlingData = _BootsCrawlingData.Find( bootsProductID );
	if( crawlingData != nullptr )
	{
		//if( crawlingData->UpdateDate.Compare( FDateTime::Today().ToString() ) == 0 )
		if( crawlingData->FIreBaseDBVersion == _FIreBaseCrawlingDBVersion )
		{
			FBM_LOG_FUNCTION_INFO( Log, TEXT( "Already CrawlingData [ %s ] " ), *bootsProductID );
			return crawlingData;
		}
		else
		{
			isModify = true;
		}
	}

	if ( B_FIREBASE )
	{
		FST_BOOTS_CRAWLING_DATA newData;
		bool isSuccess = B_FIREBASE->GetDataBaseCrawlingData( "BootsInfo/" + bootsProductID, newData );
		if( isSuccess )
		{
			// 쇼핑몰 Data 정렬하기
			if( newData.CrawlingInfo.Num() > 1 )
			{
				newData.CrawlingInfo.ValueSort([]( const FST_BOOTS_CRAWLING_INFO_DATA& A, const FST_BOOTS_CRAWLING_INFO_DATA& B ){
					return A.PriceData < B.PriceData;
				});
			}
			
			newData.FIreBaseDBVersion = _FIreBaseCrawlingDBVersion;
			
			newData.UpdateDate = FDateTime::Today().ToString();
			if( isModify )
			{
				_BootsCrawlingData[bootsProductID] = newData;
			}
			else
			{
				_BootsCrawlingData.Add( bootsProductID, newData );
			}

			SaveFile();
			FBM_LOG_FUNCTION_INFO( Log, TEXT( "Save CrawlingData [ %s ] " ), *bootsProductID );
			return _BootsCrawlingData.Find( bootsProductID );
		}
	}

	return nullptr;
}

void UFBM_SaveGame::AddBookMarkBoots( const int32 bootsIndex )
{
	_MyBookMarkBoots.AddUnique( bootsIndex );
	SaveFile();

	GInst->PlayWarningUI( 67 );
}

void UFBM_SaveGame::RemoveBookMarkBoots( const int32 bootsIndex )
{
	_MyBookMarkBoots.Remove( bootsIndex );
	SaveFile();

	GInst->PlayWarningUI( 68 );
}

TArray<int32> UFBM_SaveGame::GetBookMarkBoots() const
{
	return _MyBookMarkBoots;
}

bool UFBM_SaveGame::IsBookMarkBoots( int32 bootsIndex ) const
{
	int32 findIndex = _MyBookMarkBoots.Find( bootsIndex );
	return findIndex != INDEX_NONE;
}

void UFBM_SaveGame::SetMainBannerData( TArray<FST_MAIN_BANNER_DATA> mainBannerData, bool isNowSave /*= false */ )
{
	_MainBannerData = mainBannerData;

	if( isNowSave )
	{
		SaveFile();
	}
}

const TArray<FST_MAIN_BANNER_DATA>& UFBM_SaveGame::GetMainBannerData() const
{
	return _MainBannerData;
}

void UFBM_SaveGame::SetNoticeData( TArray<FST_NOTICE_DATA> noticeData, bool isNowSave/* = false */)
{
	_NoticeData = noticeData;

	if( isNowSave )
	{
		SaveFile();
	}
}

const TArray<FST_NOTICE_DATA>& UFBM_SaveGame::GetNoticeData() const
{
	return _NoticeData;
}

void UFBM_SaveGame::SetFaqData( TArray<FST_FAQ_DATA> faqData, bool isNowSave /*= false */ )
{
	_FaqData = faqData;

	if( isNowSave )
	{
		SaveFile();
	}
}

const TArray<FST_FAQ_DATA>& UFBM_SaveGame::GetFaqData() const
{
	return _FaqData;
}

void UFBM_SaveGame::SetUpcomingData( TArray<FST_UPCOMING_DATA> upcomingData, bool isNowSave /*= false */ )
{
	_UpcomingData = upcomingData;

	if( isNowSave )
	{
		SaveFile();
	}
}

const TArray<FST_UPCOMING_DATA>& UFBM_SaveGame::GetUpcomingData() const
{
	return _UpcomingData;
}

void UFBM_SaveGame::AddSearchData( const FString addSearchText, bool isNowSave/* = false */ )
{
	int32 findIndex = _SearchData.Find( addSearchText );
	if ( findIndex != INDEX_NONE )
	{
		_SearchData.RemoveAt( findIndex );
	}
	else
	{
		if( _SearchData.Num() > 9 )
		{
			_SearchData.RemoveAt( 0 );
		}
	}

	_SearchData.AddUnique( addSearchText );

	if( isNowSave )
	{
		SaveFile();
	}
}

const TArray<FString>& UFBM_SaveGame::GetSearchData() const
{
	return _SearchData;
}

void UFBM_SaveGame::DeleteSearchData()
{
	_SearchData.Empty();

	SaveFile();
}

void UFBM_SaveGame::UpdateFireBaseCrawlingDBVersion()
{
	if( B_FIREBASE )
	{
		FST_BOOTS_CRAWLING_DATA newData;
		uint32 curFireBaseCrawlingDBVer = B_FIREBASE->GetDataBaseIntValue( "FBM_Ver" );
		if( curFireBaseCrawlingDBVer > 0 )
		{
			_FIreBaseCrawlingDBVersion = curFireBaseCrawlingDBVer;

			SaveFile();
			FBM_LOG_FUNCTION_INFO( Log, TEXT( "Save FireBase Crawling DB Version [ %d ] " ), curFireBaseCrawlingDBVer );
		}
	}
}

bool UFBM_SaveGame::UpdateFireBaseDetailDBVersion()
{
	bool isChangeVer = false;

	if( B_FIREBASE )
	{
		FST_BOOTS_CRAWLING_DATA newData;
		uint32 curFireBaseDetailDBVer = B_FIREBASE->GetDataBaseIntValue( "FBM_Detail_Ver" );
		if( curFireBaseDetailDBVer > 0 )
		{
			if (_FIreBaseDetailDBVersion != curFireBaseDetailDBVer )
			{
				isChangeVer = true;
			}

			_FIreBaseDetailDBVersion = curFireBaseDetailDBVer;

			SaveFile();
			FBM_LOG_FUNCTION_INFO( Log, TEXT( "Save FireBase Detail DB Version [ %d ] " ), curFireBaseDetailDBVer );
		}
	}

	return isChangeVer;
}

void UFBM_SaveGame::UpdateFireBaseBootsDetailData()
{
	if( _FIreBaseDetailDBVersion <= 0 )
	{
		return;
	}

	if( B_FIREBASE )
	{
		_BootsInfoData.Empty();
		bool isSuccess = B_FIREBASE->GetDataBaseBootsDetailData( "BootsDetail", _BootsInfoData );
		if( isSuccess )
		{
			SaveFile();
			FBM_LOG_FUNCTION_INFO( Log, TEXT( "Save BootsDetailData" ) );
		}
	}
}


void UFBM_SaveGame::UpdateAppVersion()
{
	bool isChangeVer = false;

	if( B_FIREBASE )
	{
		FString curAppVer = B_FIREBASE->GetDataBaseStringValue( "Cur_Version" );
		SetCurVersion( curAppVer );
	}
}

const FST_FOOTBALL_BOOTS_DATA* UFBM_SaveGame::GetBootsInfo_DB( int32 bootsIndex )
{
	if( _FIreBaseDetailDBVersion <= 0 )
	{
		return nullptr;
	}

	return _BootsInfoData.Find( bootsIndex );
}

void UFBM_SaveGame::SearchBootsInfo_DB( FText searchText, TArray<int>& OUT_BootsInexInfoByBrand )
{
	FString searchString = searchText.ToString();
	//FBM_LOG_FUNCTION_INFO( Log, TEXT( "searchString [ %s ] " ), *searchString );
	for( auto& bootsInfo : _BootsInfoData )
	{
		// 브랜드 검색
		/*
		FString brandString = UFBMUtil::BrandNameText( arAllRows[nIndex]->eBrandType ).ToString();
		int32 findIndexBrand = searchString.Find( brandString );
		if( findIndexBrand != INDEX_NONE )
		{
			OUT_BootsInexInfoByBrand.AddUnique( arAllRows[nIndex]->nIndex );
			continue;
		}
		*/
		// Name 검색
		FString nameString = bootsInfo.Value.BootsName;
		//FBM_LOG_FUNCTION_INFO( Log, TEXT( "nameString [ %s ] " ), *nameString );
		int32 findIndex = nameString.Find( searchString );
		if( findIndex != INDEX_NONE )
		{
			OUT_BootsInexInfoByBrand.AddUnique( bootsInfo.Value.BootsIndex );
			continue;
		}
		else
		{
			int32 searchSuccessNum = 0;
			TArray<FString> searchParse = UKismetStringLibrary::ParseIntoArray( searchString );
			for( auto& parseWord : searchParse )
			{
				int32 findIndexParse = nameString.Find( parseWord );
				if( findIndexParse != INDEX_NONE )
				{
					searchSuccessNum++;
					continue;
				}
			}

			if( searchSuccessNum == searchParse.Num() )
			{
				OUT_BootsInexInfoByBrand.AddUnique( bootsInfo.Value.BootsIndex );
				continue;
			}
		}

		// 품번 검색
		FString productIDString = bootsInfo.Value.ProductID;
		int32 findIndexProductID = productIDString.Find( searchString );
		if( findIndexProductID != INDEX_NONE )
		{
			OUT_BootsInexInfoByBrand.AddUnique( bootsInfo.Value.BootsIndex );
			continue;
		}
		else
		{
			for( auto& otherID : bootsInfo.Value.Other_ProductID )
			{
				FString otherIDString = otherID;
				int32 findIndexOtherID = otherIDString.Find( searchString );
				if( findIndexOtherID != INDEX_NONE )
				{
					OUT_BootsInexInfoByBrand.AddUnique( bootsInfo.Value.BootsIndex );
					break;
				}
			}
		}
	}
}

void UFBM_SaveGame::GetBootsIndexInfoByBrandSort_DB( TArray<E_BRAND_TYPE> brandType, E_SORT_TYPE sortType, TArray<int>& OUT_BootsInexInfoByBrandSort )
{
	_BootsInfoData.ValueSort( [sortType]( FST_FOOTBALL_BOOTS_DATA A, FST_FOOTBALL_BOOTS_DATA B )
					{
						switch( sortType )
						{
						case E_SORT_TYPE::E_SORT_TYPE_NEW:
							return A.GetNewReleaseDate() >= B.GetNewReleaseDate();
						case E_SORT_TYPE::E_SORT_TYPE_PRICE_LOW:
							{
								if( A.GetLowPrice() == 0 )
								{
									return false;
								}
								else if( B.GetLowPrice() == 0 )
								{
									return true;
								}

								return A.GetLowPrice() <= B.GetLowPrice();
							}
						case E_SORT_TYPE::E_SORT_TYPE_PRICE_HIGH:
							return A.GetHighPrice() >= B.GetHighPrice();
						case E_SORT_TYPE::E_SORT_TYPE_WEIGHT_LOW:
							return A.Weight <= B.Weight;
						case E_SORT_TYPE::E_SORT_TYPE_WEIGHT_HIGH:
							return A.Weight >= B.Weight;
						case E_SORT_TYPE::E_SORT_TYPE_ABC:
							{
								FString splitStringA = A.BootsName;
								FString splitLeftA;
								FString splitRightA;
								splitStringA.Split( TEXT( " " ), &splitLeftA, &splitRightA );

								FString splitStringB = B.BootsName;
								FString splitLeftB;
								FString splitRightB;
								splitStringB.Split( TEXT( " " ), &splitLeftB, &splitRightB );

								return splitRightA <= splitRightB;
							}
						case E_SORT_TYPE::E_SORT_TYPE_ABC_REVERS:
							{
								FString splitStringA = A.BootsName;
								FString splitLeftA;
								FString splitRightA;
								splitStringA.Split( TEXT( " " ), &splitLeftA, &splitRightA );

								FString splitStringB = B.BootsName;
								FString splitLeftB;
								FString splitRightB;
								splitStringB.Split( TEXT( " " ), &splitLeftB, &splitRightB );

								return splitRightA >= splitRightB;
							}
						default:
							return A.BootsIndex < B.BootsIndex;
							break;
						}
					} );

	for( auto& bootsInfo : _BootsInfoData )
	{
		int32 findAllTypeIndex = brandType.Find( E_BRAND_TYPE::E_BRAND_TYPE_ALL );
		int32 findIndex = brandType.Find( bootsInfo.Value.BrandType );
		if( findAllTypeIndex != INDEX_NONE || findIndex != INDEX_NONE )
		{
			OUT_BootsInexInfoByBrandSort.AddUnique( bootsInfo.Value.BootsIndex );
		}
	}
}

void UFBM_SaveGame::UpdateFireBaseTeamData()
{
	if( _FIreBaseDetailDBVersion <= 0 )
	{
		return;
	}

	if( B_FIREBASE )
	{
		_TeamData.Empty();
		bool isSuccess = B_FIREBASE->GetDataBaseTeamData( "TeamInfo", _TeamData );
		if( isSuccess )
		{
			SaveFile();
			FBM_LOG_FUNCTION_INFO( Log, TEXT( "Save TeamData" ) );
		}
	}
}

void UFBM_SaveGame::UpdateFireBaseStadiumData()
{
	if( _FIreBaseDetailDBVersion <= 0 )
	{
		return;
	}

	if( B_FIREBASE )
	{
		_StadiumData.Empty();
		bool isSuccess = B_FIREBASE->GetDataBaseStadiumData( "StadiumInfo", _StadiumData );
		if( isSuccess )
		{
			SaveFile();
			FBM_LOG_FUNCTION_INFO( Log, TEXT( "Save StadiumData" ) );
		}
	}
}

void UFBM_SaveGame::UpdateFireBaseMatchData()
{
	if( _FIreBaseDetailDBVersion <= 0 )
	{
		return;
	}

	if( B_FIREBASE )
	{
		_MatchData.Empty();
		bool isSuccess = B_FIREBASE->GetDataBaseMatchData( "MatchInfo", _MatchData );
		if( isSuccess )
		{
			SaveFile();
			FBM_LOG_FUNCTION_INFO( Log, TEXT( "Save MatchData" ) );
		}
	}
}

void UFBM_SaveGame::UpdateFireBasePlayerData()
{
	if( _FIreBaseDetailDBVersion <= 0 )
	{
		return;
	}

	if( B_FIREBASE )
	{
		_PlayerData.Empty();
		bool isSuccess = B_FIREBASE->GetDataBasePlayerData( "PlayerInfo", _PlayerData );
		if( isSuccess )
		{
			SaveFile();
			FBM_LOG_FUNCTION_INFO( Log, TEXT( "Save PlayerData" ) );
		}
	}
}

void UFBM_SaveGame::UpdateFireBaseYearMvpData()
{
	if( _FIreBaseDetailDBVersion <= 0 )
	{
		return;
	}

	if( B_FIREBASE )
	{
		_YearMvpData.Empty();
		bool isSuccess = B_FIREBASE->GetDataBaseYearMvpData( "YearMvp", _YearMvpData );
		if( isSuccess )
		{
			SaveFile();
			FBM_LOG_FUNCTION_INFO( Log, TEXT( "Save YearMvpData" ) );
		}
	}
}

void UFBM_SaveGame::UpdateFireBaseYearKingData()
{
	if( _FIreBaseDetailDBVersion <= 0 )
	{
		return;
	}

	if( B_FIREBASE )
	{
		_YearKingData.Empty();
		bool isSuccess = B_FIREBASE->GetDataBaseYearKingData( "YearKing", _YearKingData );
		if( isSuccess )
		{
			SaveFile();
			FBM_LOG_FUNCTION_INFO( Log, TEXT( "Save YearKingData" ) );
		}
	}
}

void UFBM_SaveGame::UpdateFireBaseStaffData()
{
	if( _FIreBaseDetailDBVersion <= 0 )
	{
		return;
	}

	if( B_FIREBASE )
	{
		bool isSuccess = B_FIREBASE->GetDataBaseStaffData( "Staff", _StaffData );
		if( isSuccess )
		{
			SaveFile();
			FBM_LOG_FUNCTION_INFO( Log, TEXT( "Save StaffData" ) );
		}
	}
}

void UFBM_SaveGame::UpdateRecordData()
{
	for( auto& playerItem : _PlayerData )
	{
		for( auto& matchItem : _MatchData )
		{
			FString strYear = matchItem.MatchDate.Left( 4 );

			// 골 정보 업데이트
			for( auto& homeGoalItem : matchItem.HomeGoalInfo )
			{
				if( playerItem.PlayerName == homeGoalItem )
				{
					if( playerItem.GoalNum.Contains( strYear ) )
					{
						playerItem.GoalNum[strYear] = playerItem.GoalNum[strYear] + 1;

						FST_PLAYER_MATCH_DATA tmpData( matchItem.Comment, matchItem.AwayTeamName, matchItem.MatchType );
						playerItem.NewGoalData[strYear].PlayerMatchDatas.Add( tmpData );
					}
					else
					{
						playerItem.GoalNum.Add( strYear, 1 );

						FST_PLAYER_MATCH_DATA tmpData( matchItem.Comment, matchItem.AwayTeamName, matchItem.MatchType );
						FST_PLAYER_MATCH_DATAS tmpDatas;
						tmpDatas.PlayerMatchDatas.Add(tmpData);
						playerItem.NewGoalData.Add(strYear, tmpDatas );
					}

					if ( matchItem.MatchType == E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH )
					{
						if( playerItem.GoalNum_AMatch.Contains( strYear ) )
						{
							playerItem.GoalNum_AMatch[strYear] = playerItem.GoalNum_AMatch[strYear] + 1;
						}
						else
						{
							playerItem.GoalNum_AMatch.Add( strYear, 1 );
						}
					}
					else if( matchItem.MatchType == E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH )
					{
						if( playerItem.GoalNum_OwnMatch.Contains( strYear ) )
						{
							playerItem.GoalNum_OwnMatch[strYear] = playerItem.GoalNum_OwnMatch[strYear] + 1;
						}
						else
						{
							playerItem.GoalNum_OwnMatch.Add( strYear, 1 );
						}
					}
				}
			}
			for( auto& awayGoalItem : matchItem.AwayGoalInfo )
			{
				if( playerItem.PlayerName == awayGoalItem )
				{
					if( playerItem.GoalNum.Contains( strYear ) )
					{
						playerItem.GoalNum[strYear] = playerItem.GoalNum[strYear] + 1;

						FST_PLAYER_MATCH_DATA tmpData( matchItem.Comment, matchItem.AwayTeamName, matchItem.MatchType );
						playerItem.NewGoalData[strYear].PlayerMatchDatas.Add( tmpData );
					}
					else
					{
						playerItem.GoalNum.Add( strYear, 1 );

						FST_PLAYER_MATCH_DATA tmpData( matchItem.Comment, matchItem.AwayTeamName, matchItem.MatchType );
						FST_PLAYER_MATCH_DATAS tmpDatas;
						tmpDatas.PlayerMatchDatas.Add( tmpData );
						playerItem.NewGoalData.Add( strYear, tmpDatas );
					}
					if( matchItem.MatchType == E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH )
					{
						if( playerItem.GoalNum_AMatch.Contains( strYear ) )
						{
							playerItem.GoalNum_AMatch[strYear] = playerItem.GoalNum_AMatch[strYear] + 1;
						}
						else
						{
							playerItem.GoalNum_AMatch.Add( strYear, 1 );
						}
					}
					else if( matchItem.MatchType == E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH )
					{
						if( playerItem.GoalNum_OwnMatch.Contains( strYear ) )
						{
							playerItem.GoalNum_OwnMatch[strYear] = playerItem.GoalNum_OwnMatch[strYear] + 1;
						}
						else
						{
							playerItem.GoalNum_OwnMatch.Add( strYear, 1 );
						}
					}
				}
			}

			// 도움 정보 업데이트
			for( auto& homeAssistItem : matchItem.HomeAssistInfo )
			{
				if( playerItem.PlayerName == homeAssistItem )
				{
					if( playerItem.AssistNum.Contains( strYear ) )
					{
						playerItem.AssistNum[strYear] = playerItem.AssistNum[strYear] + 1;

						FST_PLAYER_MATCH_DATA tmpData( matchItem.Comment, matchItem.AwayTeamName, matchItem.MatchType );
						playerItem.NewAssistData[strYear].PlayerMatchDatas.Add( tmpData );
					}
					else
					{
						playerItem.AssistNum.Add( strYear, 1 );

						FST_PLAYER_MATCH_DATA tmpData( matchItem.Comment, matchItem.AwayTeamName, matchItem.MatchType );
						FST_PLAYER_MATCH_DATAS tmpDatas;
						tmpDatas.PlayerMatchDatas.Add( tmpData );
						playerItem.NewAssistData.Add( strYear, tmpDatas );
					}
					if( matchItem.MatchType == E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH )
					{
						if( playerItem.AssistNum_AMatch.Contains( strYear ) )
						{
							playerItem.AssistNum_AMatch[strYear] = playerItem.AssistNum_AMatch[strYear] + 1;
						}
						else
						{
							playerItem.AssistNum_AMatch.Add( strYear, 1 );
						}
					}
					else if( matchItem.MatchType == E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH )
					{
						if( playerItem.AssistNum_OwnMatch.Contains( strYear ) )
						{
							playerItem.AssistNum_OwnMatch[strYear] = playerItem.AssistNum_OwnMatch[strYear] + 1;
						}
						else
						{
							playerItem.AssistNum_OwnMatch.Add( strYear, 1 );
						}
					}
				}
			}
			for( auto& awayAssistItem : matchItem.AwayAssistInfo )
			{
				if( playerItem.PlayerName == awayAssistItem )
				{
					if( playerItem.AssistNum.Contains( strYear ) )
					{
						playerItem.AssistNum[strYear] = playerItem.AssistNum[strYear] + 1;

						FST_PLAYER_MATCH_DATA tmpData( matchItem.Comment, matchItem.AwayTeamName, matchItem.MatchType );
						playerItem.NewAssistData[strYear].PlayerMatchDatas.Add( tmpData );
					}
					else
					{
						playerItem.AssistNum.Add( strYear, 1 );

						FST_PLAYER_MATCH_DATA tmpData( matchItem.Comment, matchItem.AwayTeamName, matchItem.MatchType );
						FST_PLAYER_MATCH_DATAS tmpDatas;
						tmpDatas.PlayerMatchDatas.Add( tmpData );
						playerItem.NewAssistData.Add( strYear, tmpDatas );
					}
					if( matchItem.MatchType == E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH )
					{
						if( playerItem.AssistNum_AMatch.Contains( strYear ) )
						{
							playerItem.AssistNum_AMatch[strYear] = playerItem.AssistNum_AMatch[strYear] + 1;
						}
						else
						{
							playerItem.AssistNum_AMatch.Add( strYear, 1 );
						}
					}
					else if( matchItem.MatchType == E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH )
					{
						if( playerItem.AssistNum_OwnMatch.Contains( strYear ) )
						{
							playerItem.AssistNum_OwnMatch[strYear] = playerItem.AssistNum_OwnMatch[strYear] + 1;
						}
						else
						{
							playerItem.AssistNum_OwnMatch.Add( strYear, 1 );
						}
					}
				}
			}

			// 경기수 정보 업데이트
			for( auto& homePlayerItem : matchItem.HomePlayerInfo )
			{
				if( playerItem.PlayerName == homePlayerItem )
				{
					if( playerItem.GamesNum.Contains( strYear ) )
					{
						playerItem.GamesNum[strYear] = playerItem.GamesNum[strYear] + 1;

						FST_PLAYER_MATCH_DATA tmpData( matchItem.Comment, matchItem.AwayTeamName, matchItem.MatchType );
						playerItem.NewGamesNumData[strYear].PlayerMatchDatas.Add( tmpData );
					}
					else
					{
						playerItem.GamesNum.Add( strYear, 1 );

						FST_PLAYER_MATCH_DATA tmpData( matchItem.Comment, matchItem.AwayTeamName, matchItem.MatchType );
						FST_PLAYER_MATCH_DATAS tmpDatas;
						tmpDatas.PlayerMatchDatas.Add( tmpData );
						playerItem.NewGamesNumData.Add( strYear, tmpDatas );
					}
					if( matchItem.MatchType == E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH )
					{
						if( playerItem.GamesNum_AMatch.Contains( strYear ) )
						{
							playerItem.GamesNum_AMatch[strYear] = playerItem.GamesNum_AMatch[strYear] + 1;
						}
						else
						{
							playerItem.GamesNum_AMatch.Add( strYear, 1 );
						}
					}
					else if( matchItem.MatchType == E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH )
					{
						if( playerItem.GamesNum_OwnMatch.Contains( strYear ) )
						{
							playerItem.GamesNum_OwnMatch[strYear] = playerItem.GamesNum_OwnMatch[strYear] + 1;
						}
						else
						{
							playerItem.GamesNum_OwnMatch.Add( strYear, 1 );
						}
					}
				}
			}
			for( auto& awayPlayerItem : matchItem.AwayPlayerInfo )
			{
				if( playerItem.PlayerName == awayPlayerItem )
				{
					if( playerItem.GamesNum.Contains( strYear ) )
					{
						playerItem.GamesNum[strYear] = playerItem.GamesNum[strYear] + 1;

						FST_PLAYER_MATCH_DATA tmpData( matchItem.Comment, matchItem.AwayTeamName, matchItem.MatchType );
						playerItem.NewGamesNumData[strYear].PlayerMatchDatas.Add( tmpData );
					}
					else
					{
						playerItem.GamesNum.Add( strYear, 1 );

						FST_PLAYER_MATCH_DATA tmpData( matchItem.Comment, matchItem.AwayTeamName, matchItem.MatchType );
						FST_PLAYER_MATCH_DATAS tmpDatas;
						tmpDatas.PlayerMatchDatas.Add( tmpData );
						playerItem.NewGamesNumData.Add( strYear, tmpDatas );
					}
					if( matchItem.MatchType == E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH )
					{
						if( playerItem.GamesNum_AMatch.Contains( strYear ) )
						{
							playerItem.GamesNum_AMatch[strYear] = playerItem.GamesNum_AMatch[strYear] + 1;
						}
						else
						{
							playerItem.GamesNum_AMatch.Add( strYear, 1 );
						}
					}
					else if( matchItem.MatchType == E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH )
					{
						if( playerItem.GamesNum_OwnMatch.Contains( strYear ) )
						{
							playerItem.GamesNum_OwnMatch[strYear] = playerItem.GamesNum_OwnMatch[strYear] + 1;
						}
						else
						{
							playerItem.GamesNum_OwnMatch.Add( strYear, 1 );
						}
					}
				}
			}
		}

		// 최근 7경기 골 정보 업데이트
		int32 curMatchNum = 0;
		for( int32 matchIndex = _MatchData.Num() - 1; matchIndex >= 0; --matchIndex )
		{
			if( _MatchData[matchIndex].InfoType == E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT )
			{
				int32 curGoalNum = 0;
				for( auto& homeGoalItem : _MatchData[matchIndex].HomeGoalInfo )
				{
					if( playerItem.PlayerName == homeGoalItem )
					{
						curGoalNum++;
					}
				}

				for( auto& awayGoalItem : _MatchData[matchIndex].AwayGoalInfo )
				{
					if( playerItem.PlayerName == awayGoalItem )
					{
						curGoalNum++;
					}
				}

				playerItem.RecentDayGoalNum.Add( _MatchData[matchIndex].MatchDate, curGoalNum );
				curMatchNum++;
			}

			if ( curMatchNum >= 7)
			{
				break;
			}
		}
		playerItem.RecentDayGoalNum.KeySort( []( FString A, FString B )
											 {
												 return A < B;
											 } );

		// 최근 7경기 도움 정보 업데이트
		curMatchNum = 0;
		for( int32 matchIndex = _MatchData.Num() - 1; matchIndex >= 0; --matchIndex )
		{
			if( _MatchData[matchIndex].InfoType == E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT )
			{
				int32 curAssistNum = 0;
				for( auto& homeAssistItem : _MatchData[matchIndex].HomeAssistInfo )
				{
					if( playerItem.PlayerName == homeAssistItem )
					{
						curAssistNum++;
					}
				}

				for( auto& awayAssistItem : _MatchData[matchIndex].AwayAssistInfo )
				{
					if( playerItem.PlayerName == awayAssistItem )
					{
						curAssistNum++;
					}
				}

				playerItem.RecentDayAssistNum.Add( _MatchData[matchIndex].MatchDate, curAssistNum );
				curMatchNum++;
			}

			if( curMatchNum >= 7 )
			{
				break;
			}
		}
		playerItem.RecentDayAssistNum.KeySort( []( FString A, FString B )
											 {
												 return A < B;
											 } );

		// 최근 4주 골 정보 업데이트
		FDateTime nowDateTime = FDateTime::Now();
		FDateTime WeekDateTime1 = nowDateTime - FTimespan( 7, 0, 0, 0 );
		FDateTime WeekDateTime2 = nowDateTime - FTimespan( 14, 0, 0, 0 );
		FDateTime WeekDateTime3 = nowDateTime - FTimespan( 21, 0, 0, 0 );
		FDateTime WeekDateTime4 = nowDateTime - FTimespan( 28, 0, 0, 0 );
		FString CalcWeekDateTime1 = FString::Printf( TEXT( "%d%02d%02d" ), WeekDateTime1.GetYear(), WeekDateTime1.GetMonth(), WeekDateTime1.GetDay() );
		FString CalcWeekDateTime2 = FString::Printf( TEXT( "%d%02d%02d" ), WeekDateTime2.GetYear(), WeekDateTime2.GetMonth(), WeekDateTime2.GetDay() );
		FString CalcWeekDateTime3 = FString::Printf( TEXT( "%d%02d%02d" ), WeekDateTime3.GetYear(), WeekDateTime3.GetMonth(), WeekDateTime3.GetDay() );
		FString CalcWeekDateTime4 = FString::Printf( TEXT( "%d%02d%02d" ), WeekDateTime4.GetYear(), WeekDateTime4.GetMonth(), WeekDateTime4.GetDay() );
		int32 curGoalNum = 0;
		for( int32 matchIndex = _MatchData.Num() - 1; matchIndex >= 0; --matchIndex )
		{
			if( _MatchData[matchIndex].InfoType == E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT )
			{
				for( auto& homeGoalItem : _MatchData[matchIndex].HomeGoalInfo )
				{
					if( playerItem.PlayerName == homeGoalItem )
					{
						curGoalNum++;
					}
				}

				for( auto& awayGoalItem : _MatchData[matchIndex].AwayGoalInfo )
				{
					if( playerItem.PlayerName == awayGoalItem )
					{
						curGoalNum++;
					}
				}
			}
			if( CalcWeekDateTime1 >= _MatchData[matchIndex].MatchDate && playerItem.RecentWeekGoalNum.Num() == 0 )
			{
				playerItem.RecentWeekGoalNum.Add( TEXT("1Week"), curGoalNum );
				curGoalNum = 0;
			}
			else if( CalcWeekDateTime2 >= _MatchData[matchIndex].MatchDate && playerItem.RecentWeekGoalNum.Num() == 1 )
			{
				playerItem.RecentWeekGoalNum.Add( TEXT( "2Week" ), curGoalNum );
				curGoalNum = 0;
			}
			else if( CalcWeekDateTime3 >= _MatchData[matchIndex].MatchDate && playerItem.RecentWeekGoalNum.Num() == 2 )
			{
				playerItem.RecentWeekGoalNum.Add( TEXT( "3Week" ), curGoalNum );
				curGoalNum = 0;
			}
			else if( CalcWeekDateTime4 >= _MatchData[matchIndex].MatchDate && playerItem.RecentWeekGoalNum.Num() == 3 )
			{
				playerItem.RecentWeekGoalNum.Add( TEXT( "4Week" ), curGoalNum );
				curGoalNum = 0;
				break;
			}
		}
		playerItem.RecentWeekGoalNum.KeySort( []( FString A, FString B )
											 {
												 return A > B;
											 } );

		// 최근 4주 도움 정보 업데이트
		int32 curAssistNum = 0;
		for( int32 matchIndex = _MatchData.Num() - 1; matchIndex >= 0; --matchIndex )
		{
			if( _MatchData[matchIndex].InfoType == E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT )
			{
				for( auto& homeAssistItem : _MatchData[matchIndex].HomeAssistInfo )
				{
					if( playerItem.PlayerName == homeAssistItem )
					{
						curAssistNum++;
					}
				}

				for( auto& awayAssistItem : _MatchData[matchIndex].AwayAssistInfo )
				{
					if( playerItem.PlayerName == awayAssistItem )
					{
						curAssistNum++;
					}
				}
			}
			if( CalcWeekDateTime1 >= _MatchData[matchIndex].MatchDate && playerItem.RecentWeekAssistNum.Num() == 0 )
			{
				playerItem.RecentWeekAssistNum.Add( TEXT( "1Week" ), curAssistNum );
				curAssistNum = 0;
			}
			else if( CalcWeekDateTime2 >= _MatchData[matchIndex].MatchDate && playerItem.RecentWeekAssistNum.Num() == 1 )
			{
				playerItem.RecentWeekAssistNum.Add( TEXT( "2Week" ), curAssistNum );
				curAssistNum = 0;
			}
			else if( CalcWeekDateTime3 >= _MatchData[matchIndex].MatchDate && playerItem.RecentWeekAssistNum.Num() == 2 )
			{
				playerItem.RecentWeekAssistNum.Add( TEXT( "3Week" ), curAssistNum );
				curAssistNum = 0;
			}
			else if( CalcWeekDateTime4 >= _MatchData[matchIndex].MatchDate && playerItem.RecentWeekAssistNum.Num() == 3 )
			{
				playerItem.RecentWeekAssistNum.Add( TEXT( "4Week" ), curAssistNum );
				curAssistNum = 0;
				break;
			}
		}
		playerItem.RecentWeekAssistNum.KeySort( []( FString A, FString B )
											  {
												  return A > B;
											  } );

		// 최근 6개월 골정보
		int32 StartYear;
		int32 StartMonth;
		int32 EndYear;
		int32 EndMonth;
		int32 CurYear = nowDateTime.GetYear();
		int32 CurMonth = nowDateTime.GetMonth();
		if( CurMonth - 6 < 1)
		{
			StartYear = CurYear -1;
			StartMonth = 12 + (CurMonth - 6);
			if (StartMonth == 7)
			{
				EndYear = CurYear -1;
				EndMonth = 12;
			}
			else
			{
				EndYear = CurYear;
				EndMonth = CurMonth - 1;
			}
		}
		else
		{
			StartYear = CurYear;
			StartMonth = CurMonth - 6;
			EndYear = CurYear;
			EndMonth = CurMonth - 1;
		}
		FString StartDate = FString::Printf( TEXT( "%d%02d" ), StartYear, StartMonth );
		FString EndDate = FString::Printf( TEXT( "%d%02d" ), EndYear, EndMonth );
		//FString StartDate = FString::FromInt( StartYear ) + FString::FromInt( StartMonth );
		for( int32 matchIndex = _MatchData.Num() - 1; matchIndex >= 0; --matchIndex )
		{
			FString MatchDate = _MatchData[matchIndex].MatchDate.Left( 6 );
			if (MatchDate < StartDate)
			{
				break;
			}

			if( _MatchData[matchIndex].InfoType == E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT &&
				MatchDate >= StartDate && MatchDate <= EndDate)
			{
				for( auto& homeGoalItem : _MatchData[matchIndex].HomeGoalInfo )
				{
					if( playerItem.PlayerName == homeGoalItem )
					{
						if( playerItem.RecentMonthGoalNum.Contains( MatchDate ) )
						{
							playerItem.RecentMonthGoalNum[MatchDate] = playerItem.RecentMonthGoalNum[MatchDate] + 1;
						}
						else
						{
							playerItem.RecentMonthGoalNum.Add( MatchDate, 1 );
						}
					}
				}

				for( auto& awayGoalItem : _MatchData[matchIndex].AwayGoalInfo )
				{
					if( playerItem.PlayerName == awayGoalItem )
					{
						if( playerItem.RecentMonthGoalNum.Contains( MatchDate ) )
						{
							playerItem.RecentMonthGoalNum[MatchDate] = playerItem.RecentMonthGoalNum[MatchDate] + 1;
						}
						else
						{
							playerItem.RecentMonthGoalNum.Add( MatchDate, 1 );
						}
					}
				}

				if( playerItem.RecentMonthGoalNum.Contains( MatchDate ) == false)
				{
					playerItem.RecentMonthGoalNum.Add( MatchDate, 0 );
				}
			}
		}
		playerItem.RecentMonthGoalNum.KeySort( []( FString A, FString B )
											  {
												  return A < B;
											  } );

		// 최근 6개월 도움 정보
		for( int32 matchIndex = _MatchData.Num() - 1; matchIndex >= 0; --matchIndex )
		{
			FString MatchDate = _MatchData[matchIndex].MatchDate.Left( 6 );
			if( MatchDate < StartDate )
			{
				break;
			}

			if( _MatchData[matchIndex].InfoType == E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT &&
				MatchDate >= StartDate && MatchDate <= EndDate )
			{
				for( auto& homeAssistItem : _MatchData[matchIndex].HomeAssistInfo )
				{
					if( playerItem.PlayerName == homeAssistItem )
					{
						if( playerItem.RecentMonthAssistNum.Contains( MatchDate ) )
						{
							playerItem.RecentMonthAssistNum[MatchDate] = playerItem.RecentMonthAssistNum[MatchDate] + 1;
						}
						else
						{
							playerItem.RecentMonthAssistNum.Add( MatchDate, 1 );
						}
					}
				}

				for( auto& awayAssistItem : _MatchData[matchIndex].AwayAssistInfo )
				{
					if( playerItem.PlayerName == awayAssistItem )
					{
						if( playerItem.RecentMonthAssistNum.Contains( MatchDate ) )
						{
							playerItem.RecentMonthAssistNum[MatchDate] = playerItem.RecentMonthAssistNum[MatchDate] + 1;
						}
						else
						{
							playerItem.RecentMonthAssistNum.Add( MatchDate, 1 );
						}
					}
				}

				if( playerItem.RecentMonthAssistNum.Contains( MatchDate ) == false )
				{
					playerItem.RecentMonthAssistNum.Add( MatchDate, 0 );
				}
			}
		}
		playerItem.RecentMonthAssistNum.KeySort( []( FString A, FString B )
											   {
												   return A < B;
											   } );

	}

	SaveFile();
	FBM_LOG_FUNCTION_INFO( Log, TEXT( "Save RecordData" ) );
}

const TArray<FST_STADIUM_INFO_DATA>& UFBM_SaveGame::GetStadiumData_DB()
{
	return _StadiumData;
}

const TArray<FST_TEAM_INFO_DATA>& UFBM_SaveGame::GetTeamData_DB()
{
	return _TeamData;
}

const FString UFBM_SaveGame::GetTeamLogoURL_DB( FString teamName )
{
	for( int32 teamIndex = 0; teamIndex < _TeamData.Num(); ++teamIndex )
	{
		if( _TeamData[teamIndex].TeamName.Equals( teamName, ESearchCase::IgnoreCase ) )
		{
			return _TeamData[teamIndex].TeamLogoURL;
		}
	}

	return TEXT( "" );
}

const TArray<FST_MATCH_DATA>& UFBM_SaveGame::GetMatchData_DB()
{
	return _MatchData;
}

TArray<FST_PLAYER_DATA>& UFBM_SaveGame::GetPlayerData_DB()
{
	return _PlayerData;
}

const FST_PLAYER_DATA* UFBM_SaveGame::GetPlayerData_DB_ByName( FString playerName )
{
	for( int32 playerIndex = 0; playerIndex < _PlayerData.Num(); ++playerIndex )
	{
		if( _PlayerData[playerIndex].PlayerName.Equals( playerName, ESearchCase::IgnoreCase ) )
		{
			return &_PlayerData[playerIndex];
		}
	}
	return nullptr;
}

TArray<FST_YEAR_MVP_DATA>& UFBM_SaveGame::GetYearMvpData_DB()
{
	return _YearMvpData;
}

TArray<FST_YEAR_KING_DATA>& UFBM_SaveGame::GetYearKingData_DB()
{
	return _YearKingData;
}

FST_STAFF_DATA UFBM_SaveGame::GetStaffData_DB()
{
	return _StaffData;
}

int32 UFBM_SaveGame::GetDevUtdTeamStrIndex( FString teamName )
{
	if ( teamName == TEXT( "DevUtd 주황" ) )
	{
		return 20;
	}

	return 21;
}

FLinearColor UFBM_SaveGame::GetDevUtdTeamColor( FString teamName )
{
	if( teamName == TEXT( "DevUtd 주황" ) )
	{
		return Color_TeamOrange;
	}

	return Color_TeamGreen;
}

E_FILTER_ITEM_TYPE UFBM_SaveGame::GetDevUtdTeamType( FString teamName )
{
	if( teamName == TEXT( "DevUtd 주황" ) )
	{
		return E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_TEAM_A;
	}
	else if( teamName == TEXT( "DevUtd 형광" ) )
	{
		return E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_TEAM_B;
	}

	return E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_NONE;
}

FString UFBM_SaveGame::_GetSlotName()
{
	return TEXT("FBM_GameSlot");
}

void UFBM_SaveGame::_SetData_Windows()
{
#if PLATFORM_WINDOWS
	_SetTeamData_Windows();
	_SetStadiumData_Windows();
	_SetMatchData_Windows();
	_SetPlayerData_Windows();
	_SetMvpData_Windows();
	_SetKingData_Windows();
	_SetStaffData_Windows();
	UpdateRecordData();

	SaveFile();
#endif
}

void UFBM_SaveGame::_SetTeamData_Windows()
{
#if PLATFORM_WINDOWS
	_TeamData.Empty();
	if( _TeamData.Num() == 0 )
	{
		_TeamData.Empty();
		FST_TEAM_INFO_DATA tempData;
		tempData.TeamName = FString( TEXT( "DevUtd" ) );
		tempData.TeamLogoURL = FString( TEXT( "https://i.postimg.cc/L4zPwQMn/DevUtd.png" ) );
		_TeamData.Add( tempData );

		FST_TEAM_INFO_DATA tempData2;
		tempData2.TeamName = FString( TEXT( "DevUtd 주황" ) );
		tempData2.TeamLogoURL = FString( TEXT( "https://i.postimg.cc/L4zPwQMn/DevUtd.png" ) );
		_TeamData.Add( tempData2 );

		FST_TEAM_INFO_DATA tempData3;
		tempData3.TeamName = FString( TEXT( "DevUtd 형광" ) );
		tempData3.TeamLogoURL = FString( TEXT( "https://i.postimg.cc/L4zPwQMn/DevUtd.png" ) );
		_TeamData.Add( tempData3 );

		FST_TEAM_INFO_DATA tempData4;
		tempData4.TeamName = FString( TEXT( "카카오" ) );
		tempData4.TeamLogoURL = FString( TEXT( "https://i.postimg.cc/NMCncGXk/Kakao.jpg" ) );
		_TeamData.Add( tempData4 );

		FST_TEAM_INFO_DATA tempData5;
		tempData5.TeamName = FString( TEXT( "NC" ) );
		tempData5.TeamLogoURL = FString( TEXT( "https://i.postimg.cc/2js1kQrg/NC.jpg" ) );
		_TeamData.Add( tempData5 );
	}
#endif
}

void UFBM_SaveGame::_SetStadiumData_Windows()
{
#if PLATFORM_WINDOWS
	_StadiumData.Empty();
	if( _StadiumData.Num() == 0 )
	{
		_StadiumData.Empty();
		FST_STADIUM_INFO_DATA tempData;
		tempData.StadiumName = FString( TEXT( "광주 문형 구장" ) );
		_StadiumData.Add( tempData );

		FST_STADIUM_INFO_DATA tempData2;
		tempData2.StadiumName = FString( TEXT( "탄천 A 구장" ) );
		_StadiumData.Add( tempData2 );

		FST_STADIUM_INFO_DATA tempData3;
		tempData3.StadiumName = FString( TEXT( "탄천 B 구장" ) );
		_StadiumData.Add( tempData3 );
	}
#endif
}

void UFBM_SaveGame::_SetMatchData_Windows()
{
#if PLATFORM_WINDOWS
	_MatchData.Empty();
	if( _MatchData.Num() == 0 )
	{
		FST_MATCH_DATA tempData;
		tempData.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH;
		tempData.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT;
		tempData.HomeTeamName = TEXT( "DevUtd 주황" );
		tempData.AwayTeamName = TEXT( "NC" );
		tempData.Comment = TEXT( "광주 문형 구장" );
		tempData.MatchDate = TEXT( "20220101" );
		tempData.MatchTime = TEXT( "09:00 ~ 11:00" );
		tempData.HomeGoal = 6;
		tempData.AwayGoal = 4;
		tempData.HomeGoalInfo.Add( TEXT( "최경희" ) );
		tempData.HomeGoalInfo.Add( TEXT( "이교순" ) );
		tempData.HomeGoalInfo.Add( TEXT( "이상훈" ) );
		tempData.HomeGoalInfo.Add( TEXT( "이상훈" ) );
		tempData.AwayGoalInfo.Add( TEXT( "한승희" ) );
		tempData.AwayGoalInfo.Add( TEXT( "유원석" ) );
		tempData.AwayGoalInfo.Add( TEXT( "이승민" ) );
		tempData.AwayGoalInfo.Add( TEXT( "고정민" ) );
		tempData.AwayGoalInfo.Add( TEXT( "최성원" ) );
		tempData.HomeAssistInfo.Add( TEXT( "최경희" ) );
		tempData.HomeAssistInfo.Add( TEXT( "장희남" ) );
		tempData.HomeAssistInfo.Add( TEXT( "장희남" ) );
		tempData.HomeAssistInfo.Add( TEXT( "장희남" ) );
		tempData.AwayAssistInfo.Add( TEXT( "고정민" ) );
		tempData.HomePlayerInfo.Add( TEXT( "최경희" ) );
		tempData.HomePlayerInfo.Add( TEXT( "권기삼" ) );
		tempData.HomePlayerInfo.Add( TEXT( "김동수" ) );
		tempData.HomePlayerInfo.Add( TEXT( "장희남" ) );
		tempData.HomePlayerInfo.Add( TEXT( "채운정" ) );
		tempData.HomePlayerInfo.Add( TEXT( "이교순" ) );
		tempData.HomePlayerInfo.Add( TEXT( "하동석" ) );
		tempData.HomePlayerInfo.Add( TEXT( "이상훈" ) );
		tempData.AwayPlayerInfo.Add( TEXT( "고정민" ) );
		tempData.AwayPlayerInfo.Add( TEXT( "방정현" ) );
		tempData.AwayPlayerInfo.Add( TEXT( "박정현" ) );
		tempData.AwayPlayerInfo.Add( TEXT( "유원석" ) );
		tempData.AwayPlayerInfo.Add( TEXT( "박재형" ) );
		tempData.AwayPlayerInfo.Add( TEXT( "문경원" ) );
		tempData.AwayPlayerInfo.Add( TEXT( "이승민" ) );
		tempData.AwayPlayerInfo.Add( TEXT( "한승희" ) );
		tempData.AwayPlayerInfo.Add( TEXT( "최성원" ) );
		_MatchData.Add( tempData );

		FST_MATCH_DATA tempData2;
		tempData2.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH;
		tempData2.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT;
		tempData2.HomeTeamName = TEXT( "DevUtd 주황" );
		tempData2.AwayTeamName = TEXT( "카카오" );
		tempData2.Comment = TEXT( "탄천 A 구장" );
		tempData2.MatchDate = TEXT( "20211215" );
		tempData2.MatchTime = TEXT( "20:00 ~ 22:00" );
		tempData2.HomeGoal = 1;
		tempData2.AwayGoal = 0;
		tempData2.HomeGoalInfo.Add( TEXT( "최경희" ) );
		tempData2.HomePlayerInfo.Add( TEXT( "최경희" ) );
		tempData2.HomePlayerInfo.Add( TEXT( "권기삼" ) );
		tempData2.HomePlayerInfo.Add( TEXT( "김동수" ) );
		tempData2.HomePlayerInfo.Add( TEXT( "장희남" ) );
		tempData2.HomePlayerInfo.Add( TEXT( "채운정" ) );
		tempData2.HomePlayerInfo.Add( TEXT( "이교순" ) );
		tempData2.HomePlayerInfo.Add( TEXT( "하동석" ) );
		tempData2.HomePlayerInfo.Add( TEXT( "이상훈" ) );
		tempData2.AwayPlayerInfo.Add( TEXT( "고정민" ) );
		tempData2.AwayPlayerInfo.Add( TEXT( "방정현" ) );
		tempData2.AwayPlayerInfo.Add( TEXT( "박정현" ) );
		tempData2.AwayPlayerInfo.Add( TEXT( "유원석" ) );
		tempData2.AwayPlayerInfo.Add( TEXT( "박재형" ) );
		tempData2.AwayPlayerInfo.Add( TEXT( "문경원" ) );
		tempData2.AwayPlayerInfo.Add( TEXT( "이승민" ) );
		tempData2.AwayPlayerInfo.Add( TEXT( "한승희" ) );
		tempData2.AwayPlayerInfo.Add( TEXT( "최성원" ) );
		tempData2.AwayPlayerInfo.Add( TEXT( "정의집" ) );
		_MatchData.Add( tempData2 );

		FST_MATCH_DATA tempData3;
		tempData3.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH;
		tempData3.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE;
		tempData3.HomeTeamName = TEXT( "DevUtd" );
		tempData3.AwayTeamName = TEXT( "카카오" );
		tempData3.Comment = TEXT( "탄천 A 구장" );
		tempData3.MatchDate = TEXT( "20211230" );
		tempData3.MatchTime = TEXT( "20:00 ~ 22:00" );
		_MatchData.Add( tempData3 );

		FST_MATCH_DATA tempData4;
		tempData4.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH;
		tempData4.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE;
		tempData4.HomeTeamName = TEXT( "DevUtd" );
		tempData4.AwayTeamName = TEXT( "NC" );
		tempData4.Comment = TEXT( "탄천 B 구장" );
		tempData4.MatchDate = TEXT( "20220102" );
		tempData4.MatchTime = TEXT( "09:00 ~ 11:00" );
		_MatchData.Add( tempData4 );

		FST_MATCH_DATA tempData6;
		tempData6.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH;
		tempData6.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE;
		tempData6.HomeTeamName = TEXT( "DevUtd" );
		tempData6.AwayTeamName = TEXT( "카카오" );
		tempData6.Comment = TEXT( "탄천 B 구장" );
		tempData6.MatchDate = TEXT( "20220102" );
		tempData6.MatchTime = TEXT( "18:00 ~ 20:00" );
		_MatchData.Add( tempData6 );

		FST_MATCH_DATA tempData5;
		tempData5.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH;
		tempData5.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE;
		tempData5.HomeTeamName = TEXT( "DevUtd" );
		tempData5.AwayTeamName = TEXT( "NC" );
		tempData5.Comment = TEXT( "탄천 B 구장" );
		tempData5.MatchDate = TEXT( "20220103" );
		tempData5.MatchTime = TEXT( "20:00 ~ 22:00" );
		_MatchData.Add( tempData5 );

		FST_MATCH_DATA tempData7;
		tempData7.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH;
		tempData7.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE;
		tempData7.HomeTeamName = TEXT( "카카오" );
		tempData7.AwayTeamName = TEXT( "NC" );
		tempData7.Comment = TEXT( "탄천 B 구장" );
		tempData7.MatchDate = TEXT( "20220303" );
		tempData7.MatchTime = TEXT( "20:00 ~ 22:00" );
		_MatchData.Add( tempData7 );

		FST_MATCH_DATA tempData8;
		tempData8.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH;
		tempData8.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE;
		tempData8.HomeTeamName = TEXT( "DevUtd" );
		tempData8.AwayTeamName = TEXT( "NC" );
		tempData8.Comment = TEXT( "탄천 A 구장" );
		tempData8.MatchDate = TEXT( "20220203" );
		tempData8.MatchTime = TEXT( "20:00 ~ 22:00" );
		_MatchData.Add( tempData8 );

		FST_MATCH_DATA tempData9;
		tempData9.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH;
		tempData9.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE;
		tempData9.HomeTeamName = TEXT( "DevUtd" );
		tempData9.AwayTeamName = TEXT( "카카오" );
		tempData9.Comment = TEXT( "탄천 A 구장" );
		tempData9.MatchDate = TEXT( "20220201" );
		tempData9.MatchTime = TEXT( "20:00 ~ 22:00" );
		_MatchData.Add( tempData9 );

		FST_MATCH_DATA tempData10;
		tempData10.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH;
		tempData10.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE;
		tempData10.HomeTeamName = TEXT( "DevUtd 주황" );
		tempData10.AwayTeamName = TEXT( "DevUtd 형광" );
		tempData10.Comment = TEXT( "광주 문형 구장" );
		tempData10.MatchDate = TEXT( "20220111" );
		tempData10.MatchTime = TEXT( "20:00 ~ 22:00" );
		_MatchData.Add( tempData10 );

		FST_MATCH_DATA tempData11;
		tempData11.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH;
		tempData11.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE;
		tempData11.HomeTeamName = TEXT( "DevUtd 주황" );
		tempData11.AwayTeamName = TEXT( "DevUtd 형광" );
		tempData11.Comment = TEXT( "광주 문형 구장" );
		tempData11.MatchDate = TEXT( "20220119" );
		tempData11.MatchTime = TEXT( "20:00 ~ 22:00" );
		_MatchData.Add( tempData11 );

		FST_MATCH_DATA tempData12;
		tempData12.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH;
		tempData12.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE;
		tempData12.HomeTeamName = TEXT( "DevUtd 주황" );
		tempData12.AwayTeamName = TEXT( "DevUtd 형광" );
		tempData12.Comment = TEXT( "광주 문형 구장" );
		tempData12.MatchDate = TEXT( "20220117" );
		tempData12.MatchTime = TEXT( "20:00 ~ 22:00" );
		_MatchData.Add( tempData12 );

		FST_MATCH_DATA tempData13;
		tempData13.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH;
		tempData13.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE;
		tempData13.HomeTeamName = TEXT( "DevUtd 주황" );
		tempData13.AwayTeamName = TEXT( "DevUtd 형광" );
		tempData13.Comment = TEXT( "광주 문형 구장" );
		tempData13.MatchDate = TEXT( "20220121" );
		tempData13.MatchTime = TEXT( "20:00 ~ 22:00" );
		_MatchData.Add( tempData13 );

		FST_MATCH_DATA tempData14;
		tempData14.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH;
		tempData14.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT;
		tempData14.HomeTeamName = TEXT( "DevUtd" );
		tempData14.AwayTeamName = TEXT( "카카오" );
		tempData14.Comment = TEXT( "탄천 A 구장" );
		tempData14.MatchDate = TEXT( "20220215" );
		tempData14.MatchTime = TEXT( "20:00 ~ 22:00" );
		tempData14.HomeGoal = 1;
		tempData14.AwayGoal = 0;
		tempData14.HomeGoalInfo.Add( TEXT( "최경희" ) );
		tempData14.HomeGoalInfo.Add( TEXT( "김동수" ) );
		tempData14.HomeAssistInfo.Add( TEXT( "장희남" ) );
		tempData14.HomePlayerInfo.Add( TEXT( "최경희" ) );
		tempData14.HomePlayerInfo.Add( TEXT( "권기삼" ) );
		tempData14.HomePlayerInfo.Add( TEXT( "김동수" ) );
		tempData14.HomePlayerInfo.Add( TEXT( "장희남" ) );
		tempData14.HomePlayerInfo.Add( TEXT( "채운정" ) );
		tempData14.HomePlayerInfo.Add( TEXT( "이교순" ) );
		tempData14.HomePlayerInfo.Add( TEXT( "하동석" ) );
		tempData14.HomePlayerInfo.Add( TEXT( "이상훈" ) );
		tempData14.AwayPlayerInfo.Add( TEXT( "고정민" ) );
		tempData14.AwayPlayerInfo.Add( TEXT( "방정현" ) );
		tempData14.AwayPlayerInfo.Add( TEXT( "박정현" ) );
		tempData14.AwayPlayerInfo.Add( TEXT( "유원석" ) );
		tempData14.AwayPlayerInfo.Add( TEXT( "박재형" ) );
		tempData14.AwayPlayerInfo.Add( TEXT( "문경원" ) );
		tempData14.AwayPlayerInfo.Add( TEXT( "이승민" ) );
		tempData14.AwayPlayerInfo.Add( TEXT( "한승희" ) );
		tempData14.AwayPlayerInfo.Add( TEXT( "최성원" ) );
		_MatchData.Add( tempData14 );

		FST_MATCH_DATA tempData15;
		tempData15.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH;
		tempData15.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT;
		tempData15.HomeTeamName = TEXT( "DevUtd" );
		tempData15.AwayTeamName = TEXT( "NC" );
		tempData15.Comment = TEXT( "탄천 A 구장" );
		tempData15.MatchDate = TEXT( "20220205" );
		tempData15.MatchTime = TEXT( "20:00 ~ 22:00" );
		tempData15.HomeGoal = 1;
		tempData15.AwayGoal = 0;
		tempData15.HomeGoalInfo.Add( TEXT( "최경희" ) );
		tempData15.HomeGoalInfo.Add( TEXT( "김동수" ) );
		tempData15.HomeAssistInfo.Add( TEXT( "장희남" ) );
		tempData15.HomePlayerInfo.Add( TEXT( "최경희" ) );
		tempData15.HomePlayerInfo.Add( TEXT( "권기삼" ) );
		tempData15.HomePlayerInfo.Add( TEXT( "김동수" ) );
		tempData15.HomePlayerInfo.Add( TEXT( "장희남" ) );
		tempData15.HomePlayerInfo.Add( TEXT( "채운정" ) );
		tempData15.HomePlayerInfo.Add( TEXT( "이교순" ) );
		tempData15.HomePlayerInfo.Add( TEXT( "하동석" ) );
		tempData15.HomePlayerInfo.Add( TEXT( "이상훈" ) );
		tempData15.AwayPlayerInfo.Add( TEXT( "고정민" ) );
		tempData15.AwayPlayerInfo.Add( TEXT( "방정현" ) );
		tempData15.AwayPlayerInfo.Add( TEXT( "박정현" ) );
		tempData15.AwayPlayerInfo.Add( TEXT( "유원석" ) );
		tempData15.AwayPlayerInfo.Add( TEXT( "박재형" ) );
		tempData15.AwayPlayerInfo.Add( TEXT( "문경원" ) );
		tempData15.AwayPlayerInfo.Add( TEXT( "이승민" ) );
		tempData15.AwayPlayerInfo.Add( TEXT( "한승희" ) );
		tempData15.AwayPlayerInfo.Add( TEXT( "최성원" ) );
		tempData15.AwayPlayerInfo.Add( TEXT( "정의집" ) );
		_MatchData.Add( tempData15 );

		FST_MATCH_DATA tempData16;
		tempData16.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH;
		tempData16.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT;
		tempData16.HomeTeamName = TEXT( "DevUtd 주황" );
		tempData16.AwayTeamName = TEXT( "DevUtd 형광" );
		tempData16.Comment = TEXT( "탄천 A 구장" );
		tempData16.MatchDate = TEXT( "20220203" );
		tempData16.MatchTime = TEXT( "20:00 ~ 22:00" );
		tempData16.HomeGoal = 1;
		tempData16.AwayGoal = 0;
		tempData16.HomeGoalInfo.Add( TEXT( "최경희" ) );
		tempData16.HomeGoalInfo.Add( TEXT( "김동수" ) );
		tempData16.HomeGoalInfo.Add( TEXT( "정의집" ) );
		tempData16.HomeAssistInfo.Add( TEXT( "장희남" ) );
		tempData16.HomePlayerInfo.Add( TEXT( "최경희" ) );
		tempData16.HomePlayerInfo.Add( TEXT( "권기삼" ) );
		tempData16.HomePlayerInfo.Add( TEXT( "김동수" ) );
		tempData16.HomePlayerInfo.Add( TEXT( "장희남" ) );
		tempData16.HomePlayerInfo.Add( TEXT( "채운정" ) );
		tempData16.HomePlayerInfo.Add( TEXT( "이교순" ) );
		tempData16.HomePlayerInfo.Add( TEXT( "하동석" ) );
		tempData16.HomePlayerInfo.Add( TEXT( "이상훈" ) );
		tempData16.AwayPlayerInfo.Add( TEXT( "고정민" ) );
		tempData16.AwayPlayerInfo.Add( TEXT( "방정현" ) );
		tempData16.AwayPlayerInfo.Add( TEXT( "박정현" ) );
		tempData16.AwayPlayerInfo.Add( TEXT( "유원석" ) );
		tempData16.AwayPlayerInfo.Add( TEXT( "박재형" ) );
		tempData16.AwayPlayerInfo.Add( TEXT( "문경원" ) );
		tempData16.AwayPlayerInfo.Add( TEXT( "이승민" ) );
		tempData16.AwayPlayerInfo.Add( TEXT( "한승희" ) );
		tempData16.AwayPlayerInfo.Add( TEXT( "최성원" ) );
		_MatchData.Add( tempData16 );

		FST_MATCH_DATA tempData17;
		tempData17.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH;
		tempData17.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT;
		tempData17.HomeTeamName = TEXT( "DevUtd 주황" );
		tempData17.AwayTeamName = TEXT( "DevUtd 형광" );
		tempData17.Comment = TEXT( "탄천 A 구장" );
		tempData17.MatchDate = TEXT( "20220223" );
		tempData17.MatchTime = TEXT( "20:00 ~ 22:00" );
		tempData17.HomeGoal = 1;
		tempData17.AwayGoal = 0;
		tempData17.HomePlayerInfo.Add( TEXT( "최경희" ) );
		tempData17.HomePlayerInfo.Add( TEXT( "권기삼" ) );
		tempData17.HomePlayerInfo.Add( TEXT( "김동수" ) );
		tempData17.HomePlayerInfo.Add( TEXT( "장희남" ) );
		tempData17.HomePlayerInfo.Add( TEXT( "채운정" ) );
		tempData17.HomePlayerInfo.Add( TEXT( "이교순" ) );
		tempData17.HomePlayerInfo.Add( TEXT( "하동석" ) );
		tempData17.HomePlayerInfo.Add( TEXT( "이상훈" ) );
		tempData17.AwayPlayerInfo.Add( TEXT( "고정민" ) );
		tempData17.AwayPlayerInfo.Add( TEXT( "방정현" ) );
		tempData17.AwayPlayerInfo.Add( TEXT( "박정현" ) );
		tempData17.AwayPlayerInfo.Add( TEXT( "유원석" ) );
		tempData17.AwayPlayerInfo.Add( TEXT( "박재형" ) );
		tempData17.AwayPlayerInfo.Add( TEXT( "문경원" ) );
		tempData17.AwayPlayerInfo.Add( TEXT( "이승민" ) );
		tempData17.AwayPlayerInfo.Add( TEXT( "한승희" ) );
		tempData17.AwayPlayerInfo.Add( TEXT( "최성원" ) );
		_MatchData.Add( tempData17 );

		FST_MATCH_DATA tempData18;
		tempData18.MatchType = E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH;
		tempData18.InfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT;
		tempData18.HomeTeamName = TEXT( "DevUtd 주황" );
		tempData18.AwayTeamName = TEXT( "DevUtd 형광" );
		tempData18.Comment = TEXT( "탄천 A 구장" );
		tempData18.MatchDate = TEXT( "20220123" );
		tempData18.MatchTime = TEXT( "20:00 ~ 22:00" );
		tempData18.HomeGoal = 1;
		tempData18.AwayGoal = 0;
		tempData18.HomePlayerInfo.Add( TEXT( "최경희" ) );
		tempData18.HomePlayerInfo.Add( TEXT( "권기삼" ) );
		tempData18.HomePlayerInfo.Add( TEXT( "김동수" ) );
		tempData18.HomePlayerInfo.Add( TEXT( "장희남" ) );
		tempData18.HomePlayerInfo.Add( TEXT( "채운정" ) );
		tempData18.HomePlayerInfo.Add( TEXT( "이교순" ) );
		tempData18.HomePlayerInfo.Add( TEXT( "하동석" ) );
		tempData18.HomePlayerInfo.Add( TEXT( "이상훈" ) );
		tempData18.HomePlayerInfo.Add( TEXT( "하동석" ) );
		tempData18.HomePlayerInfo.Add( TEXT( "유지웅" ) );
		tempData18.HomePlayerInfo.Add( TEXT( "이윤형" ) );
		tempData18.HomePlayerInfo.Add( TEXT( "이진호" ) );
		tempData18.AwayPlayerInfo.Add( TEXT( "고정민" ) );
		tempData18.AwayPlayerInfo.Add( TEXT( "방정현" ) );
		tempData18.AwayPlayerInfo.Add( TEXT( "박정현" ) );
		tempData18.AwayPlayerInfo.Add( TEXT( "유원석" ) );
		tempData18.AwayPlayerInfo.Add( TEXT( "박재형" ) );
		tempData18.AwayPlayerInfo.Add( TEXT( "문경원" ) );
		tempData18.AwayPlayerInfo.Add( TEXT( "이승민" ) );
		tempData18.AwayPlayerInfo.Add( TEXT( "한승희" ) );
		tempData18.AwayPlayerInfo.Add( TEXT( "최성원" ) );
		_MatchData.Add( tempData18 );
	}
#endif
}

void UFBM_SaveGame::_SetPlayerData_Windows()
{
#if PLATFORM_WINDOWS
	_PlayerData.Empty();
	if( _PlayerData.Num() == 0 )
	{
		FST_PLAYER_DATA tempData;
		tempData.PlayerName = FString( TEXT( "최경희" ) );
		tempData.TeamName = FString( TEXT( "DevUtd 주황" ) );
		tempData.PictureURL = FString( TEXT( "https://i.postimg.cc/rscdC4gf/CKH.jpg" ) );
		tempData.MvpNum = 3;
		_PlayerData.Add( tempData );

		FST_PLAYER_DATA tempData2;
		tempData2.PlayerName = FString( TEXT( "채운정" ) );
		tempData2.TeamName = FString( TEXT( "DevUtd 주황" ) );
		tempData2.PictureURL = FString( TEXT( "" ) );
		tempData2.MvpNum = 0;
		_PlayerData.Add( tempData2 );

		FST_PLAYER_DATA tempData3;
		tempData3.PlayerName = FString( TEXT( "고정민" ) );
		tempData3.TeamName = FString( TEXT( "DevUtd 형광" ) );
		tempData3.PictureURL = FString( TEXT( "" ) );
		tempData3.MvpNum = 0;
		_PlayerData.Add( tempData3 );

		FST_PLAYER_DATA tempData4;
		tempData4.PlayerName = FString( TEXT( "최성원" ) );
		tempData4.TeamName = FString( TEXT( "DevUtd 형광" ) );
		tempData4.PictureURL = FString( TEXT( "" ) );
		tempData4.MvpNum = 0;
		_PlayerData.Add( tempData4 );

		FST_PLAYER_DATA tempData5;
		tempData5.PlayerName = FString( TEXT( "김동수" ) );
		tempData5.TeamName = FString( TEXT( "DevUtd 주황" ) );
		tempData5.PictureURL = FString( TEXT( "" ) );
		tempData5.MvpNum = 0;
		_PlayerData.Add( tempData5 );

		FST_PLAYER_DATA tempData6;
		tempData6.PlayerName = FString( TEXT( "장희남" ) );
		tempData6.TeamName = FString( TEXT( "DevUtd 주황" ) );
		tempData6.PictureURL = FString( TEXT( "" ) );
		tempData6.MvpNum = 0;
		_PlayerData.Add( tempData6 );

		FST_PLAYER_DATA tempData7;
		tempData7.PlayerName = FString( TEXT( "정의집" ) );
		tempData7.TeamName = FString( TEXT( "DevUtd 형광" ) );
		tempData7.PictureURL = FString( TEXT( "" ) );
		tempData7.MvpNum = 0;
		_PlayerData.Add( tempData7 );
	}
#endif
}

void UFBM_SaveGame::_SetMvpData_Windows()
{
#if PLATFORM_WINDOWS
	_YearMvpData.Empty();
	if( _YearMvpData.Num() == 0 )
	{
		FST_YEAR_MVP_DATA mvpData;
		mvpData.Year = FString( TEXT( "2023" ) );
		mvpData.Name.Add(FString( TEXT( "최경희" ) ));
		mvpData.Name.Add( FString( TEXT( "고정민" ) ) );
		//mvpData.Name.Add( FString( TEXT( "장희남" ) ) );
		_YearMvpData.Add( mvpData );
	}
#endif
}

void UFBM_SaveGame::_SetKingData_Windows()
{
#if PLATFORM_WINDOWS
	_YearKingData.Empty();
	if( _YearKingData.Num() == 0 )
	{
		FST_YEAR_KING_DATA kingData;
		kingData.Year = FString( TEXT( "2023" ) );
		kingData.GoalKing = FString( TEXT( "고정민" ) );
		kingData.AssistKing = FString( TEXT( "최경희" ) );
		kingData.TotalPointKing = FString( TEXT( "고정민" ) );
		kingData.AttendanceKing = FString( TEXT( "채운정" ) );
		_YearKingData.Add( kingData );
	}
#endif
}

void UFBM_SaveGame::_SetStaffData_Windows()
{
#if PLATFORM_WINDOWS
	_StaffData.Owner = FString( TEXT( "고정민" ) );
	_StaffData.GeneralManager = FString( TEXT( "채운정" ) );
	_StaffData.HeadCoach = FString( TEXT( "최성원" ) );
	_StaffData.SecondCoach = FString( TEXT( "최경희" ) );
	_StaffData.ThirdCoach = FString( TEXT( "" ) );
	_StaffData.FourthCoach = FString( TEXT( "" ) );
#endif
}
