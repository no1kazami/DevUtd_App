// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "InstanceId/InstanceIdDeleteToken.h"
#include "UltimateMobileKit.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
#include "firebase/instance_id.h"
#include "firebase/util.h"
#endif

FFirebaseInstanceIdDeleteToken::FFirebaseInstanceIdDeleteToken(FUltimateMobileKit* InSubsystem, const FOnFirebaseInstanceIdDeleteTokenCompleteDelegate& InDelegate)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
{
}

void FFirebaseInstanceIdDeleteToken::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseInstanceIdDeleteToken async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInstanceIdPtr FirebaseInstanceId = UltimateMobileKit->GetFirebaseInstanceId();

		if (FirebaseInstanceId.IsValid() && FirebaseInstanceId->IsInitialized())
		{
			NativeInstanceId = FirebaseInstanceId->GetFirebaseNativeInstanceId();

			if(NativeInstanceId.IsValid())
			{
				FetchFutureResult = NativeInstanceId->DeleteToken();
				return;
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseInstanceIdDeleteToken::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	if (FetchFutureResult.status() == firebase::kFutureStatusComplete)
	{
		Error = FFirebaseInstanceId::FirebaseErrorFromNative(static_cast<firebase::instance_id::Error>(FetchFutureResult.error()));

		if (Error == EFirebaseInstanceIdError::None)
		{
			bWasSuccessful = true;
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseInstanceIdDeleteToken Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseInstanceIdDeleteToken::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseInstanceIdDeleteToken async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, Error);
}

void FFirebaseInstanceIdDeleteToken::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	FetchFutureResult.Release();
#endif
}
