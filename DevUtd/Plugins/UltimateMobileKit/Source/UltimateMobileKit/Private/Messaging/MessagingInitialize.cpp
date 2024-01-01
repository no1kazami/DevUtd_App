// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Messaging/MessagingInitialize.h"
#include "UltimateMobileKit.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
#include "firebase/messaging.h"
#include "firebase/util.h"
#endif


FFirebaseMessagingInitialize::FFirebaseMessagingInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseMessagingInitializeCompleteDelegate& InDelegate, bool InRequestPermission, const FFirebaseMessaging* InFirebaseMessaging)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, RequestPermission(InRequestPermission)
	, FirebaseMessaging(InFirebaseMessaging)
{
}

void FFirebaseMessagingInitialize::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseMessagingInitialize async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAppPtr FirebaseApp = UltimateMobileKit->GetFirebaseApp();

		if (FirebaseApp.IsValid() && FirebaseApp->IsInitialized())
		{
			FFirebaseNativeAppPtr NativeApp = FirebaseApp->GetFirebaseNativeApp();

			if (NativeApp.IsValid())
			{
				static bool StaticRequestPermission = RequestPermission;

				Initializer.Initialize(NativeApp.Get(), nullptr, [](firebase::App* app, void*)
				{
					FUltimateMobileKit* InternalUltimateMobileKit = FUltimateMobileKit::Get();
					if (InternalUltimateMobileKit)
					{
						firebase::messaging::MessagingOptions MessagingOptions;
						MessagingOptions.suppress_notification_permission_prompt = !StaticRequestPermission;

						return firebase::messaging::Initialize(*app, InternalUltimateMobileKit->GetFirebaseMessaging().Get(), MessagingOptions);
					}

					return firebase::messaging::Initialize(*app, nullptr);
				});

				return;
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseMessagingInitialize::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	firebase::Future<void> LastResult = Initializer.InitializeLastResult();
	if (LastResult.status() == firebase::kFutureStatusComplete)
	{
		if (LastResult.error() == 0)
		{
			bWasSuccessful = true;
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseMessagingInitialize Error: %s"), *FString(LastResult.error_message()));
		}
		bIsComplete = true;
	}

	if (Initializer.InitializeLastResult().status() == firebase::kFutureStatusInvalid)
	{
		bWasSuccessful = false;
		bIsComplete = true;
	}
	LastResult.Release();
#endif
}

void FFirebaseMessagingInitialize::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseMessagingInitialize async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful);
}

void FFirebaseMessagingInitialize::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseMessagingPtr InternalFirebaseMessaging = UltimateMobileKit->GetFirebaseMessaging();

		if (InternalFirebaseMessaging.IsValid())
		{
			InternalFirebaseMessaging->SetInitialized(bWasSuccessful);
		}
	}
#endif
}
