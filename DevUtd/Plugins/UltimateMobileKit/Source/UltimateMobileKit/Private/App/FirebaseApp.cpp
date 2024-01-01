// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "App/FirebaseApp.h"
#include "UltimateMobileKit.h"
#include "UltimateMobileKitSettings.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "App/AppMakeGooglePlayAvailable.h"

#if WITH_ULTIMATEMOBILEKIT
#if PLATFORM_IOS
#import <FirebaseCore/FIRApp.h>
#import <FirebaseCore/FIROptions.h>
#elif PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include <android_native_app_glue.h>
#include "google_play_services/availability.h"
#endif
#endif

FFirebaseApp::FFirebaseApp()
{
}

FFirebaseApp::~FFirebaseApp()
{
}

const bool FFirebaseApp::Init()
{
	if (IsInitialized())
	{
		return true;
	}

	// Settings
	const UUltimateMobileKitSettings* DefaultSettings = GetDefault<UUltimateMobileKitSettings>();

#if WITH_ULTIMATEMOBILEKIT
	if (firebase::App::GetInstance() == nullptr)
	{
#if PLATFORM_IOS
		FirebaseNativeAppPtr = MakeShareable(firebase::App::Create(firebase::AppOptions()));
#elif PLATFORM_ANDROID
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		jobject Activity = FAndroidApplication::GetGameActivityThis();

		if (Env && Activity)
		{
			FirebaseNativeAppPtr = MakeShareable(firebase::App::Create(firebase::AppOptions(), Env, Activity));
		}
		else
		{
			return false;
		}
#endif
	}
	else
	{
		FirebaseNativeAppPtr = MakeShareable(firebase::App::GetInstance());
	}

	bool bWasSuccessfullyInitialized = FirebaseNativeAppPtr.IsValid();
	SetInitialized(bWasSuccessfullyInitialized);

	return bWasSuccessfullyInitialized;
#else
	return false;
#endif
}

void FFirebaseApp::Shutdown()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase App Shutdown"));

#if WITH_ULTIMATEMOBILEKIT
	FirebaseNativeAppPtr = nullptr;
#endif
}

const bool FFirebaseApp::IsInitialized() const
{
	return bInitialized;
}

void FFirebaseApp::SetInitialized(const bool Initialized)
{
	bInitialized = Initialized;

	if (bInitialized)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase App is initialized successfully"));
	}
	else
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase App is not initialized"));
	}
}

const EGooglePlayAvailability FFirebaseApp::CheckGooglePlayAvailability() const
{
#if WITH_ULTIMATEMOBILEKIT && PLATFORM_ANDROID
	if (IsInitialized())
	{
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		jobject Activity = FAndroidApplication::GetGameActivityThis();

		if (Env && Activity)
		{
			google_play_services::Availability GooglePlayAvailability = google_play_services::CheckAvailability(Env, Activity);

			switch (GooglePlayAvailability)
			{
			case google_play_services::kAvailabilityAvailable:
				return EGooglePlayAvailability::Available;
			case google_play_services::kAvailabilityUnavailableDisabled:
				return EGooglePlayAvailability::UnavailableDisabled;
			case google_play_services::kAvailabilityUnavailableInvalid:
				return EGooglePlayAvailability::UnavailableInvalid;
			case google_play_services::kAvailabilityUnavailableMissing:
				return EGooglePlayAvailability::UnavailableMissing;
			case google_play_services::kAvailabilityUnavailableOther:
				return EGooglePlayAvailability::UnavailableOther;
			case google_play_services::kAvailabilityUnavailablePermissions:
				return EGooglePlayAvailability::UnavailablePermissions;
			case google_play_services::kAvailabilityUnavailableUpdateRequired:
				return EGooglePlayAvailability::UnavailableUpdateRequired;
			case google_play_services::kAvailabilityUnavailableUpdating:
				return EGooglePlayAvailability::UnavailableUpdating;
			default:
				return EGooglePlayAvailability::UnavailableMissing;
			}
		}
	}
#endif

	return EGooglePlayAvailability::UnavailableMissing;
}

void FFirebaseApp::MakeGooglePlayAvailable(const FOnFirebaseMakeGooglePlayAvailableCompleteDelegate& Delegate /*= FOnFirebaseMakeGooglePlayAvailableCompleteDelegate()*/) const
{
#if WITH_ULTIMATEMOBILEKIT && PLATFORM_ANDROID
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAppMakeGooglePlayAvailable(UltimateMobileKit->Get(), Delegate);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}
#endif

	Delegate.ExecuteIfBound(false);
}
