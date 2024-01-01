// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthLinkWithCredential.h"
#include "UltimateMobileKit.h"

FFirebaseAuthLinkWithCredential::FFirebaseAuthLinkWithCredential(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthLinkWithCredentialCompleteDelegate& InDelegate, const UFirebaseCredential* InCredential) : FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, Credential(InCredential)
{
}

void FFirebaseAuthLinkWithCredential::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseAuthLinkWithCredential %s async task..."), *UFirebaseCredential::ProviderToString(Credential->GetType()));

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
					FetchFutureResult = CurrentUser->LinkWithCredential(Credential->GetNativeCredential());

					return;
				}
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseAuthLinkWithCredential::Tick()
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
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseAuthLinkWithCredential %s Error: %s"), *UFirebaseCredential::ProviderToString(Credential->GetType()), *FString(FetchFutureResult.error_message()));
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

void FFirebaseAuthLinkWithCredential::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseAuthLinkWithCredential %s async task %s"), *UFirebaseCredential::ProviderToString(Credential->GetType()), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, Error);
}

void FFirebaseAuthLinkWithCredential::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FetchFutureResult.Release();
#endif
}
