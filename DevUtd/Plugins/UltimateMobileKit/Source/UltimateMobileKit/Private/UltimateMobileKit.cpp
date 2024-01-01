// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "UltimateMobileKit.h"
#include "UltimateMobileKitSettings.h"
#include "UltimateMobileKitAsyncTaskManager.h"

#if WITH_ULTIMATEMOBILEKIT
#if PLATFORM_IOS
#import <FirebaseCore/FIRApp.h>
#import <FirebaseCore/FIROptions.h>
#elif PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include <android_native_app_glue.h>
#endif
#endif

#if WITH_ULTIMATEMOBILEKIT
#include "firebase/app.h"
#endif

DEFINE_LOG_CATEGORY(LogUltimateMobileKit);

FUltimateMobileKit::FUltimateMobileKit(FName InInstanceName)
	: FOnlineSubsystemImpl(TEXT("UltimateMobileKit"), InInstanceName)
	, FirebaseAppPtr(nullptr)
	, FirebaseAnalyticsPtr(nullptr)
	, FirebaseAuthPtr(nullptr)
	, FirebaseConfigPtr(nullptr)
	, FirebaseCrashlyticsPtr(nullptr)
	, FirebaseInAppMessagingPtr(nullptr)
	, FirebaseInstanceIdPtr(nullptr)
	, FirebaseInvitesPtr(nullptr)
	, FirebaseLinksPtr(nullptr)
	, FirebaseMessagingPtr(nullptr)
	, FirebasePerformancePtr(nullptr)
	, FirebaseStoragePtr(nullptr)
	, FirebaseTestLabPtr(nullptr)
	, FirebaseDataBasePtr(nullptr)
{
}

FUltimateMobileKit::~FUltimateMobileKit()
{
	FirebaseAppPtr = nullptr;
	FirebaseAnalyticsPtr = nullptr;
	FirebaseAuthPtr = nullptr;
	FirebaseConfigPtr = nullptr;
	FirebaseCrashlyticsPtr = nullptr;
	FirebaseInAppMessagingPtr = nullptr;
	FirebaseInstanceIdPtr = nullptr;
	FirebaseInvitesPtr = nullptr;
	FirebaseLinksPtr = nullptr;
	FirebaseMessagingPtr = nullptr;
	FirebasePerformancePtr = nullptr;
	FirebaseStoragePtr = nullptr;
	FirebaseTestLabPtr = nullptr;
	FirebaseDataBasePtr = nullptr;
}

bool FUltimateMobileKit::Init()
{
	bool bSuccessfullyStartedUp = true;

	OnlineAsyncTaskThreadRunnable.Reset(new FUltimateMobileKitAsyncTaskManager);
	OnlineAsyncTaskThread.Reset(FRunnableThread::Create(OnlineAsyncTaskThreadRunnable.Get(), *FString::Printf(TEXT("OnlineAsyncTaskThread %s"), *InstanceName.ToString())));

	// Instantiate modules
	FirebaseAppPtr = MakeShareable(new FFirebaseApp());
	FirebaseAnalyticsPtr = MakeShareable(new FFirebaseAnalytics());
	FirebaseAuthPtr = MakeShareable(new FFirebaseAuth());
	FirebaseConfigPtr = MakeShareable(new FFirebaseConfig());
	FirebaseCrashlyticsPtr = MakeShareable(new FFirebaseCrashlytics());
	FirebaseInAppMessagingPtr = MakeShareable(new FFirebaseInAppMessaging());
	FirebaseInstanceIdPtr = MakeShareable(new FFirebaseInstanceId());
	FirebaseInvitesPtr = MakeShareable(new FFirebaseInvites());
	FirebaseLinksPtr = MakeShareable(new FFirebaseLinks());
	FirebaseMessagingPtr = MakeShareable(new FFirebaseMessaging());
	FirebasePerformancePtr = MakeShareable(new FFirebasePerformance());
	FirebaseStoragePtr = MakeShareable(new FFirebaseStorage());
	FirebaseTestLabPtr = MakeShareable(new FFirebaseTestLab());
	FirebaseDataBasePtr = MakeShareable( new FirebaseDataBase_CKH() );

	// Init Firebase App
	bool bInitSuccessful = FirebaseAppPtr->Init();

	// Init Firebase Crashlytics && Firebase Performance Monitoring
	if (bInitSuccessful)
	{
		FirebaseCrashlyticsPtr->Init();
		FirebasePerformancePtr->Init();
		FirebaseTestLabPtr->Init();
	}

	return bInitSuccessful;
}

bool FUltimateMobileKit::Shutdown()
{
	bool bSuccessfullyShutdown = true;

	FirebaseAppPtr->Shutdown();
	FirebaseAnalyticsPtr->Shutdown();
	FirebaseAuthPtr->Shutdown();
	FirebaseConfigPtr->Shutdown();
	FirebaseCrashlyticsPtr->Shutdown();
	FirebaseInAppMessagingPtr->Shutdown();
	FirebaseInstanceIdPtr->Shutdown();
	FirebaseInvitesPtr->Shutdown();
	FirebaseLinksPtr->Shutdown();
	FirebaseMessagingPtr->Shutdown();
	FirebasePerformancePtr->Shutdown();
	FirebaseStoragePtr->Shutdown();
	FirebaseTestLabPtr->Shutdown();
	FirebaseDataBasePtr->Shutdown();

	FirebaseAppPtr = nullptr;
	FirebaseAnalyticsPtr = nullptr;
	FirebaseAuthPtr = nullptr;
	FirebaseConfigPtr = nullptr;
	FirebaseCrashlyticsPtr = nullptr;
	FirebaseInAppMessagingPtr = nullptr;
	FirebaseInstanceIdPtr = nullptr;
	FirebaseInvitesPtr = nullptr;
	FirebaseLinksPtr = nullptr;
	FirebaseMessagingPtr = nullptr;
	FirebasePerformancePtr = nullptr;
	FirebaseStoragePtr = nullptr;
	FirebaseTestLabPtr = nullptr;
	FirebaseDataBasePtr = nullptr;

	bSuccessfullyShutdown = FOnlineSubsystemImpl::Shutdown();

	OnlineAsyncTaskThread.Reset();
	OnlineAsyncTaskThreadRunnable.Reset();

	return bSuccessfullyShutdown;
}

bool FUltimateMobileKit::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	return false;
}

FText FUltimateMobileKit::GetOnlineServiceName() const
{
	return NSLOCTEXT("UltimateMobileKit", "OnlineServiceName", "Ultimate Mobile Kit");
}

bool FUltimateMobileKit::Tick(float DeltaTime)
{
	if (!FOnlineSubsystemImpl::Tick(DeltaTime))
	{
		return false;
	}

	if (OnlineAsyncTaskThreadRunnable)
	{
		OnlineAsyncTaskThreadRunnable->GameTick();
	}

	return true;
}

bool FUltimateMobileKit::IsEnabled() const
{
	return true;
}

IOnlineSessionPtr FUltimateMobileKit::GetSessionInterface() const
{
	return nullptr;
}

IOnlineFriendsPtr FUltimateMobileKit::GetFriendsInterface() const
{
	return nullptr;
}

IOnlineGroupsPtr FUltimateMobileKit::GetGroupsInterface() const
{
	return nullptr;
}

IOnlinePartyPtr FUltimateMobileKit::GetPartyInterface() const
{
	return nullptr;
}

IOnlineSharedCloudPtr FUltimateMobileKit::GetSharedCloudInterface() const
{
	return nullptr;
}

IOnlineUserCloudPtr FUltimateMobileKit::GetUserCloudInterface() const
{
	return nullptr;
}

IOnlineEntitlementsPtr FUltimateMobileKit::GetEntitlementsInterface() const
{
	return nullptr;
}

IOnlineLeaderboardsPtr FUltimateMobileKit::GetLeaderboardsInterface() const
{
	return nullptr;
}

IOnlineVoicePtr FUltimateMobileKit::GetVoiceInterface() const
{
	return nullptr;
}

IOnlineExternalUIPtr FUltimateMobileKit::GetExternalUIInterface() const
{
	return nullptr;
}

IOnlineTimePtr FUltimateMobileKit::GetTimeInterface() const
{
	return nullptr;
}

IOnlineIdentityPtr FUltimateMobileKit::GetIdentityInterface() const
{
	return nullptr;
}

IOnlineTitleFilePtr FUltimateMobileKit::GetTitleFileInterface() const
{
	return nullptr;
}

IOnlineStorePtr FUltimateMobileKit::GetStoreInterface() const
{
	return nullptr;
}

IOnlineStoreV2Ptr FUltimateMobileKit::GetStoreV2Interface() const
{
	return nullptr;
}

IOnlinePurchasePtr FUltimateMobileKit::GetPurchaseInterface() const
{
	return nullptr;
}

IOnlineEventsPtr FUltimateMobileKit::GetEventsInterface() const
{
	return nullptr;
}

IOnlineAchievementsPtr FUltimateMobileKit::GetAchievementsInterface() const
{
	return nullptr;
}

IOnlineSharingPtr FUltimateMobileKit::GetSharingInterface() const
{
	return nullptr;
}

IOnlineUserPtr FUltimateMobileKit::GetUserInterface() const
{
	return nullptr;
}

IOnlineMessagePtr FUltimateMobileKit::GetMessageInterface() const
{
	return nullptr;
}

IOnlinePresencePtr FUltimateMobileKit::GetPresenceInterface() const
{
	return nullptr;
}

IOnlineChatPtr FUltimateMobileKit::GetChatInterface() const
{
	return nullptr;
}

IOnlineStatsPtr FUltimateMobileKit::GetStatsInterface() const
{
	return nullptr;
}

IOnlineTurnBasedPtr FUltimateMobileKit::GetTurnBasedInterface() const
{
	return nullptr;
}

IOnlineTournamentPtr FUltimateMobileKit::GetTournamentInterface() const
{
	return nullptr;
}

FString FUltimateMobileKit::GetAppId() const
{
	return FString();
}

FFirebaseAppPtr FUltimateMobileKit::GetFirebaseApp() const
{
	return FirebaseAppPtr;
}

FFirebaseAnalyticsPtr FUltimateMobileKit::GetFirebaseAnalytics() const
{
	return FirebaseAnalyticsPtr;
}

FFirebaseAuthPtr FUltimateMobileKit::GetFirebaseAuth() const
{
	return FirebaseAuthPtr;
}

FFirebaseConfigPtr FUltimateMobileKit::GetFirebaseConfig() const
{
	return FirebaseConfigPtr;
}

FFirebaseCrashlyticsPtr FUltimateMobileKit::GetFirebaseCrashlytics() const
{
	return FirebaseCrashlyticsPtr;
}

FFirebaseInAppMessagingPtr FUltimateMobileKit::GetFirebaseInAppMessaging() const
{
	return FirebaseInAppMessagingPtr;
}

FFirebaseInstanceIdPtr FUltimateMobileKit::GetFirebaseInstanceId() const
{
	return FirebaseInstanceIdPtr;
}

FFirebaseInvitesPtr FUltimateMobileKit::GetFirebaseInvites() const
{
	return FirebaseInvitesPtr;
}

FFirebaseLinksPtr FUltimateMobileKit::GetFirebaseLinks() const
{
	return FirebaseLinksPtr;
}

FFirebaseMessagingPtr FUltimateMobileKit::GetFirebaseMessaging() const
{
	return FirebaseMessagingPtr;
}

FFirebasePerformancePtr FUltimateMobileKit::GetFirebasePerformance() const
{
	return FirebasePerformancePtr;
}

FFirebaseStoragePtr FUltimateMobileKit::GetFirebaseStorage() const
{
	return FirebaseStoragePtr;
}

FFirebaseTestLabPtr FUltimateMobileKit::GetFirebaseTestLab() const
{
	return FirebaseTestLabPtr;
}

FFirebaseDataBasePtr FUltimateMobileKit::GetFirebaseDataBase() const
{
	return FirebaseDataBasePtr;
}

void FUltimateMobileKit::QueueAsyncTask(FOnlineAsyncTask* AsyncTask)
{
	check(OnlineAsyncTaskThreadRunnable);
	OnlineAsyncTaskThreadRunnable->AddToInQueue(AsyncTask);
}
