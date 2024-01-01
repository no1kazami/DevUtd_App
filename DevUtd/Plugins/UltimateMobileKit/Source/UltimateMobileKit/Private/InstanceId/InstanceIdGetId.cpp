// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "InstanceId/InstanceIdGetId.h"
#include "UltimateMobileKit.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
#include "firebase/instance_id.h"
#include "firebase/util.h"
#endif

FFirebaseInstanceIdGetId::FFirebaseInstanceIdGetId(FUltimateMobileKit* InSubsystem, const FOnFirebaseInstanceIdGetIdCompleteDelegate& InDelegate)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
{
}

void FFirebaseInstanceIdGetId::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseInstanceIdGetId async task..."));

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
				FetchFutureResult = NativeInstanceId->GetId();
				return;
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseInstanceIdGetId::Tick()
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
			ResultId = FString(FetchFutureResult.result()->c_str());
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseInstanceIdGetId Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseInstanceIdGetId::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseInstanceIdGetId async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, Error, ResultId);
}

void FFirebaseInstanceIdGetId::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	FetchFutureResult.Release();
#endif
}
