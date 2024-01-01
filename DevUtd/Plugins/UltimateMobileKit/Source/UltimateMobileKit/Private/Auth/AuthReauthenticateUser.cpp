// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthReauthenticateUser.h"
#include "UltimateMobileKit.h"

FFirebaseAuthReauthenticateUser::FFirebaseAuthReauthenticateUser(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthReauthenticateUserCompleteDelegate& InDelegate, const UFirebaseCredential* InCredential) : FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, Credential(InCredential)
{
}

void FFirebaseAuthReauthenticateUser::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseAuthReauthenticateUser async task..."));

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
				firebase::auth::User* CurrentUser = NativeAuth->current_user();

				if (CurrentUser != nullptr)
				{
					FetchFutureResult = CurrentUser->Reauthenticate(Credential->GetNativeCredential());

					return;
				}
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseAuthReauthenticateUser::Tick()
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
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseAuthReauthenticateUser Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseAuthReauthenticateUser::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseAuthReauthenticateUser async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, Error);
}

void FFirebaseAuthReauthenticateUser::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FetchFutureResult.Release();
#endif
}
