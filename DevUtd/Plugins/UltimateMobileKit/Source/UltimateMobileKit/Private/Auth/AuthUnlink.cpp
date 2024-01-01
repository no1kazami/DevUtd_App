// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthUnlink.h"
#include "UltimateMobileKit.h"

FFirebaseAuthUnlink::FFirebaseAuthUnlink(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthUnlinkCompleteDelegate& InDelegate, const EFirebaseProvider InProvider)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, Provider(InProvider)
{
}

void FFirebaseAuthUnlink::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseAuthUnlink async task..."));

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
					FetchFutureResult = CurrentUser->Unlink(TCHAR_TO_UTF8(*UFirebaseCredential::ProviderToString(Provider)));
					return;
				}
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseAuthUnlink::Tick()
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
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseAuthUnlink Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseAuthUnlink::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseAuthUnlink async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, Error);
}

void FFirebaseAuthUnlink::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FetchFutureResult.Release();
#endif
}
