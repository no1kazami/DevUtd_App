// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthVerifyPhoneNumber.h"
#include "UltimateMobileKit.h"
#include "UltimateMobileKitSettings.h"

FFirebaseAuthVerifyPhoneNumber::FFirebaseAuthVerifyPhoneNumber(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthVerifyPhoneNumberCompleteDelegate& InDelegate, const FString& InPhoneNumber)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, PhoneNumber(InPhoneNumber)
{
}

void FFirebaseAuthVerifyPhoneNumber::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseAuthVerifyPhoneNumber async task..."));

	// Settings
	const UUltimateMobileKitSettings* DefaultSettings = GetDefault<UUltimateMobileKitSettings>();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			NativeAuth = FirebaseAuth->GetFirebaseNativeAuth();

			if (NativeAuth.IsValid() && FirebaseAuth.IsValid())
			{
				firebase::auth::PhoneAuthProvider& PhoneProvider = firebase::auth::PhoneAuthProvider::GetInstance(NativeAuth.Get());
				PhoneProvider.VerifyPhoneNumber(TCHAR_TO_UTF8(*PhoneNumber), 0, nullptr, this);
				return;
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseAuthVerifyPhoneNumber::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}
}

void FFirebaseAuthVerifyPhoneNumber::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseAuthVerifyPhoneNumber async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));
}

void FFirebaseAuthVerifyPhoneNumber::Finalize()
{
}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
void FFirebaseAuthVerifyPhoneNumber::OnVerificationCompleted(firebase::auth::Credential Credential)
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Phone Listener: successful automatic verification."));

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_PhoneNumberVerificationCompleted"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_PhoneNumberVerificationCompleted, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
			Delegate.ExecuteIfBound(true, EFirebaseAuthError::None, FString(), UFirebaseCredential::MakeNativeCredential(Credential, EFirebaseProvider::Phone));
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_PhoneNumberVerificationCompleted),
		nullptr,
		ENamedThreads::GameThread
	);
	
	bWasSuccessful = true;
	bIsComplete = true;
}

void FFirebaseAuthVerifyPhoneNumber::OnVerificationFailed(const std::string& Error)
{
	UE_LOG(LogUltimateMobileKit, Error, TEXT("Firebase Phone Listener: verification failed with error, %s"), *FString(Error.c_str()));
	
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_PhoneNumberVerificationFailed"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_PhoneNumberVerificationFailed, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
			Delegate.ExecuteIfBound(false, EFirebaseAuthError::UnknownError, FString(), nullptr);
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_PhoneNumberVerificationFailed),
		nullptr,
		ENamedThreads::GameThread
	);

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseAuthVerifyPhoneNumber::OnCodeSent(const std::string& VerificationId, const firebase::auth::PhoneAuthProvider::ForceResendingToken& ForceResendingToken)
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Phone Listener: code sent. verification_id=%s"), *FString(VerificationId.c_str()));

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_PhoneNumberCodeSent"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_PhoneNumberCodeSent, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
			Delegate.ExecuteIfBound(true, EFirebaseAuthError::None, FString(VerificationId.c_str()), nullptr);
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_PhoneNumberCodeSent),
		nullptr,
		ENamedThreads::GameThread
	);

	bWasSuccessful = true;
	bIsComplete = true;
}
#endif
