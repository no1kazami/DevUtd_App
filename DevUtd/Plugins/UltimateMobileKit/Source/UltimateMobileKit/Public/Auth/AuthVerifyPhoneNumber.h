// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseAuthDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
#include "firebase/auth.h"
#endif

class FUltimateMobileKit;

/** Start the phone number authentication operation. */
class FFirebaseAuthVerifyPhoneNumber 
	: public FOnlineAsyncTaskBasic<FUltimateMobileKit>
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	, public firebase::auth::PhoneAuthProvider::Listener
#endif
{
public:
	FFirebaseAuthVerifyPhoneNumber(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthVerifyPhoneNumberCompleteDelegate& InDelegate, const FString& InPhoneNumber);

	virtual FString ToString() const override { return TEXT("FirebaseAuthVerifyPhoneNumber"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	/** Phone number auto-verification succeeded. */
	virtual void OnVerificationCompleted(firebase::auth::Credential Credential) override;

	/** Phone number verification failed with an error. */
	virtual void OnVerificationFailed(const std::string& Error) override;

	/** SMS message with verification code sent to phone number. */
	virtual void OnCodeSent(const std::string& VerificationId, const firebase::auth::PhoneAuthProvider::ForceResendingToken& ForceResendingToken) override;
#endif

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthVerifyPhoneNumberCompleteDelegate Delegate;
	const FString PhoneNumber;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FFirebaseNativeAuthPtr NativeAuth;
	FFirebaseAuthPtr FirebaseAuth;
#endif
};
