// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "OnlineSubsystem.h"
#include "OnlineSubsystemImpl.h"
#include "EngineMinimal.h"

#include "App/FirebaseApp.h"
#include "Analytics/FirebaseAnalytics.h"
#include "Auth/FirebaseAuth.h"
#include "Config/FirebaseConfig.h"
#include "Crashlytics/FirebaseCrashlytics.h"
#include "InAppMessaging/FirebaseInAppMessaging.h"
#include "InstanceId/FirebaseInstanceId.h"
#include "Invites/FirebaseInvites.h"
#include "Links/FirebaseLinks.h"
#include "Messaging/FirebaseMessaging.h"
#include "Performance/FirebasePerformance.h"
#include "Storage/FirebaseStorage.h"
#include "TestLab/FirebaseTestLab.h"
#include "DataBase_CKH/FirebaseDataBase_CKH.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUltimateMobileKit, Log, All);

typedef TSharedPtr<FFirebaseApp, ESPMode::ThreadSafe> FFirebaseAppPtr;
typedef TSharedPtr<FFirebaseAnalytics, ESPMode::ThreadSafe> FFirebaseAnalyticsPtr;
typedef TSharedPtr<FFirebaseAuth, ESPMode::ThreadSafe> FFirebaseAuthPtr;
typedef TSharedPtr<FFirebaseConfig, ESPMode::ThreadSafe> FFirebaseConfigPtr;
typedef TSharedPtr<FFirebaseCrashlytics, ESPMode::ThreadSafe> FFirebaseCrashlyticsPtr;
typedef TSharedPtr<FFirebaseInAppMessaging, ESPMode::ThreadSafe> FFirebaseInAppMessagingPtr;
typedef TSharedPtr<FFirebaseInstanceId, ESPMode::ThreadSafe> FFirebaseInstanceIdPtr;
typedef TSharedPtr<FFirebaseInvites, ESPMode::ThreadSafe> FFirebaseInvitesPtr;
typedef TSharedPtr<FFirebaseLinks, ESPMode::ThreadSafe> FFirebaseLinksPtr;
typedef TSharedPtr<FFirebaseMessaging, ESPMode::ThreadSafe> FFirebaseMessagingPtr;
typedef TSharedPtr<FFirebasePerformance, ESPMode::ThreadSafe> FFirebasePerformancePtr;
typedef TSharedPtr<FFirebaseStorage, ESPMode::ThreadSafe> FFirebaseStoragePtr;
typedef TSharedPtr<FFirebaseTestLab, ESPMode::ThreadSafe> FFirebaseTestLabPtr;
typedef TSharedPtr<FirebaseDataBase_CKH, ESPMode::ThreadSafe> FFirebaseDataBasePtr;

class FRunnableThread;

/** Implementation of the online subsystem for Firebase services */
class ULTIMATEMOBILEKIT_API FUltimateMobileKit : public FOnlineSubsystemImpl
{
public:
	FUltimateMobileKit(FName InInstanceName);
	virtual ~FUltimateMobileKit();
	virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;
	virtual FText GetOnlineServiceName() const override;
	virtual bool Tick(float DeltaTime) override;
	virtual bool Init() override;
	virtual bool Shutdown() override;
	virtual bool IsEnabled() const override;

	static FUltimateMobileKit* Get()
	{
		FOnlineSubsystemModule& OSSModule = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>(TEXT("OnlineSubsystem"));
		return (FUltimateMobileKit*) OSSModule.GetOnlineSubsystem(TEXT("UltimateMobileKit"));
	}

	virtual IOnlineSessionPtr GetSessionInterface() const override;
	virtual IOnlineFriendsPtr GetFriendsInterface() const override;
	virtual IOnlineGroupsPtr GetGroupsInterface() const override;
	virtual IOnlinePartyPtr GetPartyInterface() const override;
	virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override;
	virtual IOnlineUserCloudPtr GetUserCloudInterface() const override;
	virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override;
	virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override;
	virtual IOnlineVoicePtr GetVoiceInterface() const override;
	virtual IOnlineExternalUIPtr GetExternalUIInterface() const override;
	virtual IOnlineTimePtr GetTimeInterface() const override;
	virtual IOnlineIdentityPtr GetIdentityInterface() const override;
	virtual IOnlineTitleFilePtr GetTitleFileInterface() const override;
	virtual IOnlineStorePtr GetStoreInterface() const override;
	virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override;
	virtual IOnlinePurchasePtr GetPurchaseInterface() const override;
	virtual IOnlineEventsPtr GetEventsInterface() const override;
	virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;
	virtual IOnlineSharingPtr GetSharingInterface() const override;
	virtual IOnlineUserPtr GetUserInterface() const override;
	virtual IOnlineMessagePtr GetMessageInterface() const override;
	virtual IOnlinePresencePtr GetPresenceInterface() const override;
	virtual IOnlineChatPtr GetChatInterface() const override;
	virtual IOnlineStatsPtr GetStatsInterface() const override;
	virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override;
	virtual IOnlineTournamentPtr GetTournamentInterface() const override;
	virtual FString GetAppId() const override;

	/** Get Firebase App Core Module */
	FFirebaseAppPtr GetFirebaseApp() const;

	/** Get Firebase Analytics Module */
	FFirebaseAnalyticsPtr GetFirebaseAnalytics() const;

	/** Get Firebase Authentication Module */
	FFirebaseAuthPtr GetFirebaseAuth() const;
	
	/** Get Firebase Config Module */
	FFirebaseConfigPtr GetFirebaseConfig() const;

	/** Get Firebase Crashlytics Module */
	FFirebaseCrashlyticsPtr GetFirebaseCrashlytics() const;

	/** Get Firebase In-App Messaging Module */
	FFirebaseInAppMessagingPtr GetFirebaseInAppMessaging() const;

	/** Get Firebase Instance Id Module */
	FFirebaseInstanceIdPtr GetFirebaseInstanceId() const;

	/** Get Firebase Invites Module */
	FFirebaseInvitesPtr GetFirebaseInvites() const;

	/** Get Firebase Dynamic Links Module*/
	FFirebaseLinksPtr GetFirebaseLinks() const;

	/** Get Firebase Messaging Module */
	FFirebaseMessagingPtr GetFirebaseMessaging() const;

	/** Get Firebase Performance Module */
	FFirebasePerformancePtr GetFirebasePerformance() const;

	/** Get Firebase Storage Module*/
	FFirebaseStoragePtr GetFirebaseStorage() const;

	/** Get Firebase Test Lab Module*/
	FFirebaseTestLabPtr GetFirebaseTestLab() const;

	/** Get Firebase DataBase Module */
	FFirebaseDataBasePtr GetFirebaseDataBase() const;

	void QueueAsyncTask(class FOnlineAsyncTask* AsyncTask);

protected:

	FFirebaseAppPtr FirebaseAppPtr;
	FFirebaseAnalyticsPtr FirebaseAnalyticsPtr;
	FFirebaseAuthPtr FirebaseAuthPtr;
	FFirebaseConfigPtr FirebaseConfigPtr;
	FFirebaseCrashlyticsPtr FirebaseCrashlyticsPtr;
	FFirebaseInAppMessagingPtr FirebaseInAppMessagingPtr;
	FFirebaseInstanceIdPtr FirebaseInstanceIdPtr;
	FFirebaseInvitesPtr FirebaseInvitesPtr;
	FFirebaseLinksPtr FirebaseLinksPtr;
	FFirebaseMessagingPtr FirebaseMessagingPtr;
	FFirebasePerformancePtr FirebasePerformancePtr;
	FFirebaseStoragePtr FirebaseStoragePtr;
	FFirebaseTestLabPtr FirebaseTestLabPtr;
	FFirebaseDataBasePtr FirebaseDataBasePtr;

	// Async Task Stuff
	TUniquePtr<class FUltimateMobileKitAsyncTaskManager> OnlineAsyncTaskThreadRunnable;
	TUniquePtr<FRunnableThread> OnlineAsyncTaskThread;

	class FUltimateMobileKitAsyncTaskManager* GetAsyncTaskManager()
	{
		return OnlineAsyncTaskThreadRunnable.Get(); 
	}
};

typedef TSharedPtr<FUltimateMobileKit, ESPMode::ThreadSafe> FUltimateMobileKitPtr;
