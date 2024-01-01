// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthInitialize.h"
#include "UltimateMobileKit.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
#include "firebase/auth.h"
#include "firebase/util.h"
#endif

FFirebaseAuthInitialize::FFirebaseAuthInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthInitializeCompleteDelegate& InDelegate)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
{
}

void FFirebaseAuthInitialize::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseAuthInitialize async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAppPtr FirebaseApp = UltimateMobileKit->GetFirebaseApp();

		if(FirebaseApp.IsValid() && FirebaseApp->IsInitialized())
		{
			FFirebaseNativeAppPtr NativeApp = FirebaseApp->GetFirebaseNativeApp();

			if(NativeApp.IsValid())
			{
				Initializer.Initialize(NativeApp.Get(), nullptr, [](firebase::App* app, void*)
				{
					firebase::InitResult init_result;
					firebase::auth::Auth::GetAuth(app, &init_result);
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

void FFirebaseAuthInitialize::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	firebase::Future<void> LastResult = Initializer.InitializeLastResult();
	if (LastResult.status() == firebase::kFutureStatusComplete)
	{
		Error = FFirebaseAuth::FirebaseErrorFromNative(static_cast<firebase::auth::AuthError>(LastResult.error()));

		if (Error == EFirebaseAuthError::None)
		{
			bWasSuccessful = true;
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseAuthInitialize Error: %s"), *FString(LastResult.error_message()));
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

void FFirebaseAuthInitialize::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseAuthInitialize async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, Error);
}

void FFirebaseAuthInitialize::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid())
		{
			if (bWasSuccessful && FirebaseAuth->RegisterService())
			{
				FirebaseAuth->SetInitialized(true);
			}
			else
			{
				FirebaseAuth->SetInitialized(false);
			}
		}
	}
#endif
}
