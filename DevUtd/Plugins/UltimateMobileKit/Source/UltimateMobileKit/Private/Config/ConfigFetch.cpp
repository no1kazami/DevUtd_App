// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Config/ConfigFetch.h"
#include "UltimateMobileKit.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
#include "firebase/remote_config.h"
#endif

FFirebaseConfigFetch::FFirebaseConfigFetch(FUltimateMobileKit* InSubsystem, const FOnFirebaseConfigFetchCompleteDelegate& InDelegate, const int32 InCacheExpirationInSeconds) 
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, CacheExpirationInSeconds(InCacheExpirationInSeconds)
{
}

void FFirebaseConfigFetch::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseConfigFetch async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	FetchFutureResult = firebase::remote_config::Fetch((int) CacheExpirationInSeconds);
#else
	bWasSuccessful = false;
	bIsComplete = true;
#endif
}

void FFirebaseConfigFetch::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	if (FetchFutureResult.status() == firebase::kFutureStatusComplete)
	{
		// @TODO - workaround in 4.5.0 - on iOS FetchFutureResult.error() always fails
#if PLATFORM_ANDROID
		if (FetchFutureResult.error() == 0)
		{
			bWasSuccessful = true;
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseConfigFetch Error: %s"), *FString(FetchFutureResult.error_message()));
		}
		bIsComplete = true;
#elif PLATFORM_IOS
		const firebase::remote_config::ConfigInfo& ConfigInfo = firebase::remote_config::GetInfo();

		if (ConfigInfo.last_fetch_status == firebase::remote_config::LastFetchStatus::kLastFetchStatusSuccess)
		{
			bWasSuccessful = true;
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseConfigFetch Error: %s"), *FString(FetchFutureResult.error_message()));
		}
		bIsComplete = true;
#endif
	}

	if (FetchFutureResult.status() == firebase::kFutureStatusInvalid)
	{
		bWasSuccessful = false;
		bIsComplete = true;
	}
#endif
}

void FFirebaseConfigFetch::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseConfigFetch async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful);
}

void FFirebaseConfigFetch::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	FetchFutureResult.Release();
#endif
}
