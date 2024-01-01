// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthUpdateUserProfile.h"
#include "UltimateMobileKit.h"

FFirebaseAuthUpdateUserProfile::FFirebaseAuthUpdateUserProfile(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthCreateUserEmailCompleteDelegate& InDelegate, const FFirebaseUserProfile& InUserProfile)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, Profile(InUserProfile)
{
}

void FFirebaseAuthUpdateUserProfile::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseAuthUpdateUserProfile async task..."));

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
					TSharedPtr<firebase::auth::User::UserProfile, ESPMode::ThreadSafe> NativeUserProfile = MakeShareable(new firebase::auth::User::UserProfile());

					TSharedPtr<std::string, ESPMode::ThreadSafe> DisplayNameShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*Profile.DisplayName)));
					if(!Profile.DisplayName.IsEmpty())
					{
						NativeUserProfile->display_name = DisplayNameShared->c_str();
					}

					TSharedPtr<std::string, ESPMode::ThreadSafe> PhotoUrlShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*Profile.PhotoUrl)));
					if (!Profile.PhotoUrl.IsEmpty())
					{
						NativeUserProfile->photo_url = PhotoUrlShared->c_str();
					}

					FetchFutureResult = CurrentUser->UpdateUserProfile(*(NativeUserProfile.Get()));
					return;
				}
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseAuthUpdateUserProfile::Tick()
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
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseAuthUpdateUserProfile Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseAuthUpdateUserProfile::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseAuthUpdateUserProfile async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, Error);
}

void FFirebaseAuthUpdateUserProfile::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FetchFutureResult.Release();
#endif
}
