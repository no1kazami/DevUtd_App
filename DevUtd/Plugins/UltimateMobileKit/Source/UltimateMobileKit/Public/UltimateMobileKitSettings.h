// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreUObject.h"
#include "Engine.h"
#include "UltimateMobileKitSettings.generated.h"

/** Settings for Ultimate Mobile Kit plugin */
UCLASS(config = Engine, defaultconfig)
class ULTIMATEMOBILEKIT_API UUltimateMobileKitSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UUltimateMobileKitSettings(const FObjectInitializer& ObjectInitializer);

	/** Android Bundle ID associated with Firebase App */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files Android", DisplayName = "Firebase Bundle ID")
	FString FirebaseBundleIdAndroid;

	/** Firebase App ID for Android platform */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files Android", DisplayName = "Firebase App ID")
	FString FirebaseAppIdAndroid;

	/** Firebase Client ID for Android platform */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files Android", DisplayName = "Firebase Client ID")
	TArray<FString> FirebaseClientIdAndroid;

	/** Firebase API Key for Android platform */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files Android", DisplayName = "Firebase API Key")
	FString FirebaseApiKeyAndroid;

	/** Firebase Cloud Messaging Sender ID for Android platform */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files Android", DisplayName = "Firebase Cloud Messaging Sender ID")
	FString FirebaseCloudMessagingSenderIdAndroid;

	/** Firebase Google Cloud Storage Bucket Name for Android platform */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files Android", DisplayName = "Firebase Cloud Storage Bucket Name")
	FString FirebaseGoogleCloudStorageBucketNameAndroid;

	/** Firebase Database URL for Android platform */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files Android", DisplayName = "Firebase Database URL")
	FString FirebaseDatabaseURLAndroid;

	/** IOS Bundle ID associated with Firebase App */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files IOS", DisplayName = "Firebase Bundle ID")
	FString FirebaseBundleIdIOS;

	/** Firebase App ID for IOS platform */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files IOS", DisplayName = "Firebase App ID")
	FString FirebaseAppIdIOS;

	/** Firebase Client ID for IOS platform */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files IOS", DisplayName = "Firebase Client ID")
	FString FirebaseClientIdIOS;

	/** Firebase Reversed Client ID for IOS platform */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files IOS", DisplayName = "Firebase Reversed Client ID")
	FString FirebaseReversedClientIdIOS;

	/** Firebase API Key for IOS platform */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files IOS", DisplayName = "Firebase API Key")
	FString FirebaseApiKeyIOS;

	/** Firebase Project ID for IOS platform */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files IOS", DisplayName = "Firebase Project ID")
	FString FirebaseProjectIdIOS;

	/** Firebase Cloud Messaging Sender ID for IOS platform */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files IOS", DisplayName = "Firebase Cloud Messaging Sender ID")
	FString FirebaseCloudMessagingSenderIdIOS;

	/** Firebase Google Cloud Storage Bucket Name for IOS platform */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files IOS", DisplayName = "Firebase Cloud Storage Bucket Name")
	FString FirebaseGoogleCloudStorageBucketNameIOS;

	/** Firebase Database URL for IOS platform */
	UPROPERTY(Config, EditAnywhere, Category = "Config Files IOS", DisplayName = "Firebase Database URL")
	FString FirebaseDatabaseURLIOS;

	/** Enable Firebase Analytics module */
	UPROPERTY(Config, EditAnywhere, Category = "Modules Configuration", DisplayName = "Enable Analytics")
	bool bEnableAnalytics;

	/** Enable Firebase Authentication module */
	UPROPERTY(Config, EditAnywhere, Category = "Modules Configuration", DisplayName = "Enable Authentication")
	bool bEnableAuthentication;

	/** Enable Firebase Cloud Messaging module */
	UPROPERTY(Config, EditAnywhere, Category = "Modules Configuration", DisplayName = "Enable Cloud Messaging")
	bool bEnableCloudMessaging;

	/** Enable Firebase Crashlytics module */
	UPROPERTY(Config, EditAnywhere, Category = "Modules Configuration", DisplayName = "Enable Crashlytics")
	bool bEnableCrashlytics;

	/** Enable Firebase Dynamic Links & Invites module */
	UPROPERTY(Config, EditAnywhere, Category = "Modules Configuration", DisplayName = "Enable Dynamic Links & Invites")
	bool bEnableLinksInvites;

	/** Enable Firebase In-App Messaging module */
	UPROPERTY(Config, EditAnywhere, Category = "Modules Configuration", DisplayName = "Enable In-App Messaging")
	bool bEnableInAppMessaging;

	/** Enable Firebase Instance Id module */
	UPROPERTY(Config, EditAnywhere, Category = "Modules Configuration", DisplayName = "Enable Instance Id")
	bool bEnableInstanceId;

	/** Enable Firebase Remote Config module */
	UPROPERTY(Config, EditAnywhere, Category = "Modules Configuration", DisplayName = "Enable Remote Config")
	bool bEnableRemoteConfig;

	/** Enable Firebase Performance Monitoring module */
	UPROPERTY(Config, EditAnywhere, Category = "Modules Configuration", DisplayName = "Enable Performance Monitoring")
	bool bEnablePerformanceMonitoring;

	/** Enable Firebase Storage module */
	UPROPERTY(Config, EditAnywhere, Category = "Modules Configuration", DisplayName = "Enable Storage")
	bool bEnableStorage;

	/** Enable Firebase Test Lab module (Android only) */
	UPROPERTY(Config, EditAnywhere, Category = "Modules Configuration", DisplayName = "Enable Test Lab")
	bool bEnableTestLab;

	/** Enable Firebase FireStore module By ChoiKyungHee */
	UPROPERTY( Config, EditAnywhere, Category = "Modules Configuration", DisplayName = "Enable DataBase CKH" )
	bool bEnableDataBase_CKH;

	/** Minimum engagement time required before starting the Firebase Analytics session */
	UPROPERTY(Config, EditAnywhere, Category = "Firebase Analytics")
	int32 MinimumSessionDuration;

	/** Duration of inactivity that terminates the current Firebase Analytics session */
	UPROPERTY(Config, EditAnywhere, Category = "Firebase Analytics")
	int32 SessionTimeoutDuration;

	/** Enable or disable automatic symbols upload in development mode for Firebase Crashlytics */
	UPROPERTY(Config, EditAnywhere, Category = "Firebase Crashlytics", DisplayName = "Automatic Symbols Upload for Android [Development]")
	bool bEnableCrashlyticsAutoAndroidSymbolsUploadDevelopment;

	/** Enable or disable automatic symbols upload in shipping mode for Firebase Crashlytics */
	UPROPERTY(Config, EditAnywhere, Category = "Firebase Crashlytics", DisplayName = "Automatic Symbols Upload for Android [Shipping]")
	bool bEnableCrashlyticsAutoAndroidSymbolsUploadShipping;

	/** Enable or disable debug mode for Firebase Crashlytics */
	UPROPERTY(Config, EditAnywhere, Category = "Firebase Crashlytics", DisplayName = "Enable Debug Mode")
	bool bEnableCrashlyticsDebugMode;

	/** Enable or disable developer mode (i.e disable throttling) for Remote Config */
	UPROPERTY(Config, EditAnywhere, Category = "Firebase Remote Config", DisplayName = "Enable Developer Mode")
	bool bEnableRemoteConfigDeveloperMode;

	/** Maximum time to retry a download if a failure occurs (Firebase Storage) */
	UPROPERTY(Config, EditAnywhere, Category = "Firebase Storage")
	float MaxDownloadRetryTime;

	/** Maximum time to retry operations other than upload and download if a failure occurs (Firebase Storage) */
	UPROPERTY(Config, EditAnywhere, Category = "Firebase Storage")
	float MaxOperationRetryTime;

	/** Maximum time to retry an upload if a failure occurs (Firebase Storage) */
	UPROPERTY(Config, EditAnywhere, Category = "Firebase Storage")
	float MaxUploadRetryTime;

	/** Number of game loops in Firebase Test Lab */
	UPROPERTY(Config, EditAnywhere, Category = "Firebase Test Lab")
	int32 NumberOfGameLoops;
};
