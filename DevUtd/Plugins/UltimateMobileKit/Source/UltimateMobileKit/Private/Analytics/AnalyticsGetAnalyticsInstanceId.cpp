// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Analytics/AnalyticsGetAnalyticsInstanceId.h"
#include "UltimateMobileKit.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
#include "firebase/analytics.h"
#include "firebase/util.h"
#endif

FFirebaseAnalyticsGetAnalyticsInstanceId::FFirebaseAnalyticsGetAnalyticsInstanceId(FUltimateMobileKit* InSubsystem, const FOnFirebaseAnalyticsGetAnalyticsInstanceIdCompleteDelegate& InDelegate)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
{
}

void FFirebaseAnalyticsGetAnalyticsInstanceId::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseAnalyticsGetAnalyticsInstanceId async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAnalyticsPtr FirebaseAnalytics = UltimateMobileKit->GetFirebaseAnalytics();

		if (FirebaseAnalytics.IsValid() && FirebaseAnalytics->IsInitialized())
		{
			FetchFutureResult = firebase::analytics::GetAnalyticsInstanceId();
			return;
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseAnalyticsGetAnalyticsInstanceId::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
	if (FetchFutureResult.status() == firebase::kFutureStatusComplete)
	{
		if (FetchFutureResult.error() == 0)
		{
			bWasSuccessful = true;
			ResultInstanceId = FString(FetchFutureResult.result()->c_str());
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseAnalyticsGetAnalyticsInstanceId Error: %s"), *FString(FetchFutureResult.error_message()));
		}
		bIsComplete = true;
	}

	if (FetchFutureResult.status() == firebase::kFutureStatusInvalid)
	{
		bWasSuccessful = false;
		bIsComplete = true;
	}
#endif
}

void FFirebaseAnalyticsGetAnalyticsInstanceId::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseAnalyticsGetAnalyticsInstanceId async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, ResultInstanceId);
}

void FFirebaseAnalyticsGetAnalyticsInstanceId::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
	FetchFutureResult.Release();
#endif
}
