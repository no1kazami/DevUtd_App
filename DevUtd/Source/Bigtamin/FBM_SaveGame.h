// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Util/Bigtamin_Struct.h"
#include "FBM_SaveGame.generated.h"


UCLASS()
class BIGTAMIN_API UFBM_SaveGame : public USaveGame
{
	GENERATED_BODY()

private:
	UPROPERTY()
		FString _SlotName;
	UPROPERTY()
		FString _LoginDate;
	UPROPERTY()
		FString _CurVersion;
	UPROPERTY()
		FString _ServetCheckTime;
	UPROPERTY()
		int32 _ScrollClickSensitivity = 1;
	UPROPERTY()
		FString _ReviewUrl;
	UPROPERTY()
		FString _RuleUrl;
	UPROPERTY()
		FString _SendEmailAddress;
	UPROPERTY()
		FString _ShareAppAddress;
	UPROPERTY()
		int32 _IsShowSupport = 0;
	UPROPERTY()
		int32 _IsShowPartnership = 0;
	UPROPERTY()
		int32 _NewBootsMaxCount = 0;
	UPROPERTY()
		int32 _ShowBootsDetail = 0; // (0 : 모두 오픈, 1 : 제품 정보만 오픈, 2 : 제품 정보, 리뷰 오픈, 3 : 제품 정보, 구매하기 오픈)
	UPROPERTY()
		TArray<FST_MAIN_BANNER_DATA> _MainBannerData;
	UPROPERTY()
		FString _MainBrand;
	UPROPERTY()
		TArray<FString> _MainCustomMenu;
	UPROPERTY()
		TMap<FString, FST_BOOTS_CRAWLING_DATA> _BootsCrawlingData;
	UPROPERTY()
		uint32 _FIreBaseCrawlingDBVersion = 0;
	UPROPERTY()
		TArray<int32> _MyBookMarkBoots;
	UPROPERTY()
		TArray<FST_NOTICE_DATA> _NoticeData;
	UPROPERTY()
		TArray<FST_FAQ_DATA> _FaqData;
	UPROPERTY()
		TArray<FST_UPCOMING_DATA> _UpcomingData;
	UPROPERTY()
		TArray<FString> _SearchData;
	UPROPERTY()
		TMap<int32, FST_FOOTBALL_BOOTS_DATA> _BootsInfoData;
	UPROPERTY()
		uint32 _FIreBaseDetailDBVersion = 0;

	UPROPERTY()
		TArray<FST_TEAM_INFO_DATA> _TeamData;
	UPROPERTY()
		TArray<FST_STADIUM_INFO_DATA> _StadiumData;
	UPROPERTY()
		TArray<FST_MATCH_DATA> _MatchData;
	UPROPERTY()
		TArray<FST_PLAYER_DATA> _PlayerData;
	UPROPERTY()
		TArray<FST_YEAR_MVP_DATA> _YearMvpData;
	UPROPERTY()
		TArray<FST_YEAR_KING_DATA> _YearKingData;
	UPROPERTY()
		FST_STAFF_DATA _StaffData;

public:
	UFBM_SaveGame();
	static UFBM_SaveGame& Get();

	void SaveFile();
	bool IsTodayFirstLogin( bool isNowSave = false );
	void SetCurVersion( FString configData, bool isNowSave = false );
	void SetServetCheckTime( FString configData, bool isNowSave = false );
	void SetScrollClickSensitivity( int32 configData, bool isNowSave = false );
	void SetMainBrand( FString configData, bool isNowSave = false );
	void SetMainCustomMenu( TArray<FString> configData, bool isNowSave = false );
	void SetReviewURL( FString configData, bool isNowSave = false );
	FString GetReviewURL() const;
	void SetRuleURL( FString configData, bool isNowSave = false );
	FString GetRuleURL() const;
	void SetSendEmailAddress( FString configData, bool isNowSave = false );
	FString GetSendEmailAddress() const;
	void SetShareAppAddress( FString configData, bool isNowSave = false );
	FString GetShareAppAddress() const;
	void SetShowSupport( int32 configData, bool isNowSave = false );
	bool IsShowSupport() const;
	void SetShowPartnership( int32 configData, bool isNowSave = false );
	bool IsShowPartnership() const;
	void SetNewBootsMaxCount( int32 configData, bool isNowSave = false );
	int32 GetNewBootsMaxCount() const;
	void SetShowBootsDetail( int32 configData, bool isNowSave = false );
	int32 GetShowBootsDetail() const;
	FString GetCurVersion() const;
	FString GetServetCheckTime() const;
	int32 GetScrollClickSensitivity() const;
	FString GetMainBrand() const;
	TArray<FString> GetMainCustomMenu() const;
	const FST_BOOTS_CRAWLING_DATA* GetBootsCrawlingData( FString bootsProductID );
	void AddBookMarkBoots(const int32 bootsIndex);
	void RemoveBookMarkBoots( const int32 bootsIndex );
	TArray<int32> GetBookMarkBoots() const;
	bool IsBookMarkBoots( int32 bootsIndex ) const;
	void SetMainBannerData( TArray<FST_MAIN_BANNER_DATA> mainBannerData, bool isNowSave = false );
	const TArray<FST_MAIN_BANNER_DATA>& GetMainBannerData() const;
	void SetNoticeData( TArray<FST_NOTICE_DATA> noticeData, bool isNowSave = false );
	const TArray<FST_NOTICE_DATA>& GetNoticeData() const;
	void SetFaqData( TArray<FST_FAQ_DATA> faqData, bool isNowSave = false );
	const TArray<FST_FAQ_DATA>& GetFaqData() const;
	void SetUpcomingData( TArray<FST_UPCOMING_DATA> upcomingData, bool isNowSave = false );
	const TArray<FST_UPCOMING_DATA>& GetUpcomingData() const;
	void AddSearchData(const FString addSearchText, bool isNowSave = false );
	const TArray<FString>& GetSearchData() const;
	void DeleteSearchData();
	void UpdateFireBaseCrawlingDBVersion();
	bool UpdateFireBaseDetailDBVersion();
	void UpdateFireBaseBootsDetailData();
	void UpdateAppVersion();

	const FST_FOOTBALL_BOOTS_DATA* GetBootsInfo_DB( int32 bootsIndex );
	void SearchBootsInfo_DB( FText searchText, TArray<int>& OUT_BootsInexInfoByBrand );
	void GetBootsIndexInfoByBrandSort_DB( TArray<E_BRAND_TYPE> brandType, E_SORT_TYPE sortType, TArray<int>& OUT_BootsInexInfoByBrandSort );

	void UpdateFireBaseTeamData();
	void UpdateFireBaseStadiumData();
	void UpdateFireBaseMatchData();
	void UpdateFireBasePlayerData();
	void UpdateFireBaseYearMvpData();
	void UpdateFireBaseYearKingData();
	void UpdateFireBaseStaffData();
	void UpdateRecordData();

	const TArray<FST_STADIUM_INFO_DATA>& GetStadiumData_DB();
	const TArray<FST_TEAM_INFO_DATA>& GetTeamData_DB();
	const FString GetTeamLogoURL_DB( FString teamName );
	const TArray<FST_MATCH_DATA>& GetMatchData_DB();
	TArray<FST_PLAYER_DATA>& GetPlayerData_DB();
	const FST_PLAYER_DATA* GetPlayerData_DB_ByName( FString playerName );
	TArray<FST_YEAR_MVP_DATA>& GetYearMvpData_DB();
	TArray<FST_YEAR_KING_DATA>& GetYearKingData_DB();
	FST_STAFF_DATA GetStaffData_DB();
	int32 GetDevUtdTeamStrIndex( FString teamName );
	FLinearColor GetDevUtdTeamColor( FString teamName );
	E_FILTER_ITEM_TYPE GetDevUtdTeamType( FString teamName );

private:
	static FString _GetSlotName();
	void _SetData_Windows();
	void _SetTeamData_Windows();
	void _SetStadiumData_Windows();
	void _SetMatchData_Windows();
	void _SetPlayerData_Windows();
	void _SetMvpData_Windows();
	void _SetKingData_Windows();
	void _SetStaffData_Windows();
};
