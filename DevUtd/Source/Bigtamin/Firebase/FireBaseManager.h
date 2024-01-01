// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalAccessUnit.h"
#include "UltimateMobileKit.h"
#include "FireBaseManager.generated.h"


UCLASS()
class BIGTAMIN_API UFireBaseManager : public UGlobalAccessUnit
{
	GENERATED_BODY()
public:
	TScriptDelegate <FWeakObjectPtr> MakeGooglePlayAvailableProxyOnSuccess;
	TScriptDelegate <FWeakObjectPtr> MakeGooglePlayAvailableProxyOnFail;

private:
	TArray<UFirebaseVariant*> _RemoteConfigDefaultParameters;
	TSharedPtr<FFirebaseAnalytics, ESPMode::ThreadSafe> _FirebaseAnalytics;
	TSharedPtr<FFirebaseMessaging, ESPMode::ThreadSafe> _FirebaseMessaging;
	TSharedPtr<FFirebaseConfig, ESPMode::ThreadSafe> _FirebaseRemoteConfig;
	TSharedPtr<FirebaseDataBase_CKH, ESPMode::ThreadSafe> _FirebaseDataBase;

	FString _CurVersion;
	FString _MainBrand;
	TArray<FString> _MainCustomMenu;
	bool _IsInitSuccess = false;

public:
	UFireBaseManager();
	virtual ~UFireBaseManager();
	virtual void Startup() override;
	virtual void Shutdown() override;
	virtual void LogOut() override;

public:
	void InitMyFireBase();
	bool IsInitSuccess() const;

	UFUNCTION()
		FString GetDataBaseStringValue( FString dbPath );
	UFUNCTION()
		uint32 GetDataBaseIntValue( FString dbPath );

	UFUNCTION()
		bool GetDataBaseCrawlingData( FString dbPath, FST_BOOTS_CRAWLING_DATA& OutCrawlingData );
	UFUNCTION()
		bool GetDataBaseBootsDetailData( FString dbPath, TMap<int32, FST_FOOTBALL_BOOTS_DATA>& OutBootsDetailData );
	
	//const firebase::database::DataSnapshot* GetDataBaseSnapshot( FString dbPath );

	UFUNCTION()
		bool GetDataBaseTeamData( FString dbPath, TArray<FST_TEAM_INFO_DATA>& OutTeamData );
	UFUNCTION()
		bool GetDataBaseStadiumData( FString dbPath, TArray<FST_STADIUM_INFO_DATA>& OutStadiumData );
	UFUNCTION()
		bool GetDataBaseMatchData( FString dbPath, TArray<FST_MATCH_DATA>& OutMatchData );
	UFUNCTION()
		bool GetDataBasePlayerData( FString dbPath, TArray<FST_PLAYER_DATA>& OutPlayerData );
	UFUNCTION()
		bool GetDataBaseYearMvpData( FString dbPath, TArray<FST_YEAR_MVP_DATA>& OutYearMvpData );
	UFUNCTION()
		bool GetDataBaseYearKingData( FString dbPath, TArray<FST_YEAR_KING_DATA>& OutYearKingData );
	UFUNCTION()
		bool GetDataBaseStaffData( FString dbPath, FST_STAFF_DATA& OutStaffData );
private:
	UFUNCTION()
	void _InitFirebaseAnalytics();
	UFUNCTION()
	void _InitFirebaseMessaging();
	UFUNCTION()
	void _InitFirebaseDataBase();
	UFUNCTION()
	void _InitFirebaseRemoteConfig();

	void _SuccessInit();

	UFUNCTION()
		void _OnInitFirebaseAnalyticsCompleted( bool isSuccess );
	UFUNCTION()
		void _OnInitFirebaseMessagingCompleted( bool isSuccess );
	UFUNCTION()
		void _OnInitDataBaseCompleted( bool isSuccess );
	UFUNCTION()
		void _OnInitFirebaseRemoteConfigCompleted( bool isSuccess );
	UFUNCTION()
		void _OnFetchFirebaseRemoteConfigCompleted( bool isSuccess );
	UFUNCTION()
		void _OnMakeGooglePlayAvailableProxyOnSuccess();
	UFUNCTION()
		void _OnMakeGooglePlayAvailableProxyOnFail();
	UFUNCTION()
		void _UpdateRemoteConfigData();
	UFUNCTION()
		void _UpdateDataBase();
};
