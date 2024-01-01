// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "InstanceId/InstanceIdDeleteId.h"
#include "UltimateMobileKit.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
#include "firebase/instance_id.h"
#include "firebase/util.h"
#endif

FFirebaseInstanceIdDeleteId::FFirebaseInstanceIdDeleteId(FUltimateMobileKit* InSubsystem, const FOnFirebaseInstanceIdDeleteIdCompleteDelegate& InDelegate)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
{
}

void FFirebaseInstanceIdDeleteId::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseInstanceIdDeleteId async task..."));

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
				FetchFutureResult = NativeInstanceId->DeleteId();
				return;
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseInstanceIdDeleteId::Tick()
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
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseInstanceIdDeleteId Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseInstanceIdDeleteId::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseInstanceIdDeleteId async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, Error);
}

void FFirebaseInstanceIdDeleteId::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	FetchFutureResult.Release();
#endif
}
