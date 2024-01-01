// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Messaging/MessagingRequestPermission.h"
#include "UltimateMobileKit.h"

FFirebaseMessagingRequestPermission::FFirebaseMessagingRequestPermission(FUltimateMobileKit* InSubsystem, const FOnFirebaseMessagingRequestPermissionCompleteDelegate& InDelegate)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
{
}

void FFirebaseMessagingRequestPermission::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseMessagingRequestPermission async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseMessagingPtr FirebaseMessaging = UltimateMobileKit->GetFirebaseMessaging();

		if(FirebaseMessaging.IsValid() && FirebaseMessaging->IsInitialized())
		{
			FetchFutureResult = firebase::messaging::RequestPermission();

			return;
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseMessagingRequestPermission::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	if (FetchFutureResult.status() == firebase::kFutureStatusComplete)
	{
		Error = FFirebaseMessaging::FirebaseErrorFromNative(static_cast<firebase::messaging::Error>(FetchFutureResult.error()));

		if (Error == EFirebaseMessagingError::None)
		{
			bWasSuccessful = true;
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseMessagingRequestPermission Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseMessagingRequestPermission::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseMessagingRequestPermission async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, Error);
}

void FFirebaseMessagingRequestPermission::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	FetchFutureResult.Release();
#endif
}
