// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Delegates/FirebaseDatabaseDelegates_CKH.h"
#include "Util/Bigtamin_Struct.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
#include "firebase/database.h"
#include "firebase/future.h"
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
typedef TSharedPtr<firebase::database::Database, ESPMode::ThreadSafe> FFirebaseNativeDataBasePtr;
#endif

class ULTIMATEMOBILEKIT_API FirebaseDataBase_CKH
{
public:
	FirebaseDataBase_CKH();
	virtual ~FirebaseDataBase_CKH();

	/** Initialize the Firebase DataBase CKH API  */
	void Init( const FOnFirebaseDataBaseInitializeCompleteDelegate& Delegate = FOnFirebaseDataBaseInitializeCompleteDelegate() );

	/** Shutdown the Firebase DataBase CKH API  */
	void Shutdown();

	/** Check if Firebase DataBase is initialized */
	const bool IsInitialized() const;

	/** Set Firebase DataBase initialization state */
	void SetInitialized( bool Initialized );

	/** Register Firebase DataBase services */
	const bool RegisterService();

	void AddChildListener();

	uint32 GetDataBaseIntValue( const char* dbPath );
	FString GetDataBaseStringValue( const char* dbPath );
	bool GetDataBaseCrawlingData( const char* dbPath, FST_BOOTS_CRAWLING_DATA& OutCrawlingData );
	bool GetDataBaseBootsDetailData( const char* dbPath, TMap<int32, FST_FOOTBALL_BOOTS_DATA>& OutBootsDetailData );

	bool GetDataBaseTeamData( const char* dbPath, TArray<FST_TEAM_INFO_DATA>& OutTeamData );
	bool GetDataBaseStadiumData( const char* dbPath, TArray<FST_STADIUM_INFO_DATA>& OutStadiumData );
	bool GetDataBaseMatchData( const char* dbPath, TArray<FST_MATCH_DATA>& OutMatchData );
	bool GetDataBasePlayerData( const char* dbPath, TArray<FST_PLAYER_DATA>& OutPlayerData );
	bool GetDataBaseYearMvpData( const char* dbPath, TArray<FST_YEAR_MVP_DATA>& OutYearMvpData );
	bool GetDataBaseYearKingData( const char* dbPath, TArray<FST_YEAR_KING_DATA>& OutYearKingData );
	bool GetDataBaseStaffData( const char* dbPath, FST_STAFF_DATA& OutStaffData );

	//const firebase::database::DataSnapshot* GetDataBaseSnapshot( const char* dbPath );

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	inline FFirebaseNativeDataBasePtr GetFirebaseNativeDataBase()
	{
		return FirebaseNativeDataBasePtr;
	}
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	void _WaitForCompletion( const firebase::FutureBase& future, const char* name );
#endif

private:
	bool bInitialized = false;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FFirebaseNativeDataBasePtr FirebaseNativeDataBasePtr;
#endif
};
