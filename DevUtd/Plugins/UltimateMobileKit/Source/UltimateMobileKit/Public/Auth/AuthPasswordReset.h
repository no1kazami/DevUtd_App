// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseAuthDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
#include "firebase/future.h"
#endif

class FUltimateMobileKit;

/** Initiates a password reset for the given email address */
class FFirebaseAuthPasswordReset : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAuthPasswordReset(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthPasswordResetCompleteDelegate& InDelegate, const FString& InEmail);

	virtual FString ToString() const override { return TEXT("FirebaseAuthPasswordReset"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthPasswordResetCompleteDelegate Delegate;
	const FString Email;
	EFirebaseAuthError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FFirebaseNativeAuthPtr NativeAuth;
	firebase::Future<void> FetchFutureResult;
#endif
};
