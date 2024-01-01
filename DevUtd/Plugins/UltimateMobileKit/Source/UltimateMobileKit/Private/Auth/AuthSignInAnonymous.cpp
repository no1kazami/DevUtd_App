// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthSignInAnonymous.h"
#include "UltimateMobileKit.h"

FFirebaseAuthSignInAnonymous::FFirebaseAuthSignInAnonymous(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthSignInAnonymousCompleteDelegate& InDelegate) 
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
{
}

void FFirebaseAuthSignInAnonymous::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseAuthSignInAnonymous async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			NativeAuth = FirebaseAuth->GetFirebaseNativeAuth();

			if (NativeAuth.IsValid())
			{
				FetchFutureResult = NativeAuth->SignInAnonymously();

				return;
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseAuthSignInAnonymous::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	if (FetchFutureResult.status() == firebase::kFutureStatusComplete)
	{
		Error = FFirebaseAuth::FirebaseErrorFromNative(static_cast<firebase::auth::AuthError>(FetchFutureResult.error()));

		if (Error == EFirebaseAuthError::None)
		{
			bWasSuccessful = true;
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseAuthSignInAnonymous Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseAuthSignInAnonymous::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseAuthSignInAnonymous async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, Error);
}

void FFirebaseAuthSignInAnonymous::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FetchFutureResult.Release();
#endif
}
