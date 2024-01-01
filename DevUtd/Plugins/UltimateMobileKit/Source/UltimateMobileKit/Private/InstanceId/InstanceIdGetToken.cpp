// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "InstanceId/InstanceIdGetToken.h"
#include "UltimateMobileKit.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
#include "firebase/instance_id.h"
#include "firebase/util.h"
#endif

FFirebaseInstanceIdGetToken::FFirebaseInstanceIdGetToken(FUltimateMobileKit* InSubsystem, const FOnFirebaseInstanceIdGetTokenCompleteDelegate& InDelegate)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
{
}

void FFirebaseInstanceIdGetToken::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseInstanceIdGetToken async task..."));

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
				FetchFutureResult = NativeInstanceId->GetToken();
				return;
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseInstanceIdGetToken::Tick()
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
			ResultToken = FString(FetchFutureResult.result()->c_str());
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseInstanceIdGetToken Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseInstanceIdGetToken::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseInstanceIdGetToken async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, Error, ResultToken);
}

void FFirebaseInstanceIdGetToken::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	FetchFutureResult.Release();
#endif
}
