// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "InstanceId/InstanceIdInitialize.h"
#include "UltimateMobileKit.h"

FFirebaseInstanceIdInitialize::FFirebaseInstanceIdInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseInstanceIdInitializeCompleteDelegate& InDelegate)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
{
}

void FFirebaseInstanceIdInitialize::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseInstanceIdInitialize async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAppPtr FirebaseApp = UltimateMobileKit->GetFirebaseApp();

		if (FirebaseApp.IsValid() && FirebaseApp->IsInitialized())
		{
			FFirebaseNativeAppPtr NativeApp = FirebaseApp->GetFirebaseNativeApp();

			if (NativeApp.IsValid())
			{
				Initializer.Initialize(NativeApp.Get(), nullptr, [](firebase::App* app, void*)
				{
					firebase::InitResult init_result;
					firebase::instance_id::InstanceId::GetInstanceId(app, &init_result);
					return init_result;
				});

				return;
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseInstanceIdInitialize::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	firebase::Future<void> LastResult = Initializer.InitializeLastResult();
	if (LastResult.status() == 0)
	{
		Error = FFirebaseInstanceId::FirebaseErrorFromNative(static_cast<firebase::instance_id::Error>(LastResult.error()));

		if (Error == EFirebaseInstanceIdError::None)
		{
			bWasSuccessful = true;
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseInstanceIdInitialize Error: %s"), *FString(LastResult.error_message()));
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

void FFirebaseInstanceIdInitialize::TriggerDelegates()
{
	Delegate.ExecuteIfBound(bWasSuccessful, Error);
}

void FFirebaseInstanceIdInitialize::Finalize()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseInstanceIdInitialize async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInstanceIdPtr FirebaseInstanceId = UltimateMobileKit->GetFirebaseInstanceId();

		if (FirebaseInstanceId.IsValid())
		{
			if (bWasSuccessful && FirebaseInstanceId->RegisterService())
			{
				FirebaseInstanceId->SetInitialized(true);
			}
			else
			{
				FirebaseInstanceId->SetInitialized(false);
			}
		}
	}
#endif
}
