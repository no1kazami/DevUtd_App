// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Messaging/MessagingSubscribe.h"
#include "UltimateMobileKit.h"

FFirebaseMessagingSubscribe::FFirebaseMessagingSubscribe(FUltimateMobileKit* InSubsystem, const FOnFirebaseMessagingSubscribeCompleteDelegate& InDelegate, const FString& InTopic)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, Topic(InTopic)
{
}

void FFirebaseMessagingSubscribe::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseMessagingSubscribe async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseMessagingPtr FirebaseMessaging = UltimateMobileKit->GetFirebaseMessaging();

		if(FirebaseMessaging.IsValid() && FirebaseMessaging->IsInitialized())
		{
			FetchFutureResult = firebase::messaging::Subscribe(TCHAR_TO_UTF8(*Topic));

			return;
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseMessagingSubscribe::Tick()
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
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseMessagingSubscribe Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseMessagingSubscribe::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseMessagingSubscribe async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, Error);
}

void FFirebaseMessagingSubscribe::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	FetchFutureResult.Release();
#endif
}
