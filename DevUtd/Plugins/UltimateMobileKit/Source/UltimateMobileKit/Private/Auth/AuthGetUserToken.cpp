// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthGetUserToken.h"
#include "UltimateMobileKit.h"

FFirebaseAuthGetUserToken::FFirebaseAuthGetUserToken(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthGetUserTokenCompleteDelegate& InDelegate, const bool InForceRefresh)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, ForceRefresh(InForceRefresh)
{
}

void FFirebaseAuthGetUserToken::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseAuthGetUserToken async task..."));

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
					FetchFutureResult = CurrentUser->GetToken(ForceRefresh);
					return;
				}
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseAuthGetUserToken::Tick()
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
			ResultToken = FString(FetchFutureResult.result()->c_str());
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseAuthGetUserToken Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseAuthGetUserToken::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseAuthGetUserToken async task %s, token: %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"), *ResultToken);

	Delegate.ExecuteIfBound(bWasSuccessful, Error, ResultToken);
}

void FFirebaseAuthGetUserToken::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FetchFutureResult.Release();
#endif
}
