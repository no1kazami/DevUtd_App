// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "App/AppMakeGooglePlayAvailable.h"
#include "UltimateMobileKit.h"

#if WITH_ULTIMATEMOBILEKIT && PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include <android_native_app_glue.h>
#include "google_play_services/availability.h"
#endif

FFirebaseAppMakeGooglePlayAvailable::FFirebaseAppMakeGooglePlayAvailable(FUltimateMobileKit* InSubsystem, const FOnFirebaseMakeGooglePlayAvailableCompleteDelegate& InDelegate)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
{
}

void FFirebaseAppMakeGooglePlayAvailable::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseAppMakeGooglePlayAvailable async task..."));

#if WITH_ULTIMATEMOBILEKIT && PLATFORM_ANDROID
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		jobject Activity = FAndroidApplication::GetGameActivityThis();

		if (Env && Activity)
		{
			FetchFutureResult = google_play_services::MakeAvailable(Env, Activity);
			return;
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseAppMakeGooglePlayAvailable::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT
	if (FetchFutureResult.status() == firebase::kFutureStatusComplete)
	{
		if (FetchFutureResult.error() == 0)
		{
			bWasSuccessful = true;
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseAppMakeGooglePlayAvailable Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseAppMakeGooglePlayAvailable::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseAppMakeGooglePlayAvailable async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful);
}

void FFirebaseAppMakeGooglePlayAvailable::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT
	FetchFutureResult.Release();
#endif
}
