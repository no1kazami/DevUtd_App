// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Analytics/AnalyticsInitialize.h"
#include "UltimateMobileKit.h"
#include "UltimateMobileKitSettings.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
#include "firebase/analytics.h"
#include "firebase/util.h"
#endif

FFirebaseAnalyticsInitialize::FFirebaseAnalyticsInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseAnalyticsInitializeCompleteDelegate& InDelegate)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
{
}

void FFirebaseAnalyticsInitialize::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseAnalyticsInitialize async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		// Settings
		const UUltimateMobileKitSettings* DefaultSettings = GetDefault<UUltimateMobileKitSettings>();

		firebase::analytics::Initialize(*UltimateMobileKit->GetFirebaseApp()->GetFirebaseNativeApp().Get());
		firebase::analytics::SetAnalyticsCollectionEnabled(true);
		firebase::analytics::SetMinimumSessionDuration(DefaultSettings->MinimumSessionDuration);
		firebase::analytics::SetSessionTimeoutDuration(DefaultSettings->SessionTimeoutDuration);

		UE_LOG(LogUltimateMobileKit, Display, TEXT("Initializing default settings for Firebase Analytics. Minimum Session Duration: %d, Session Timeout Duration: %d"), DefaultSettings->MinimumSessionDuration, DefaultSettings->SessionTimeoutDuration);

		bWasSuccessful = true;
		bIsComplete = true;
	}
	else
	{
		bWasSuccessful = false;
		bIsComplete = true;
	}
#else
	bWasSuccessful = false;
	bIsComplete = true;
#endif
}

void FFirebaseAnalyticsInitialize::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}
}

void FFirebaseAnalyticsInitialize::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseAnalyticsInitialize async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful);
}

void FFirebaseAnalyticsInitialize::Finalize()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAnalyticsPtr FirebaseAnalytics = UltimateMobileKit->GetFirebaseAnalytics();

		if (FirebaseAnalytics.IsValid())
		{
			FirebaseAnalytics->SetInitialized(bWasSuccessful);
		}
	}
}
