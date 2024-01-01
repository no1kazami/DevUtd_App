// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseAuthDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
#include "firebase/future.h"
#include "firebase/auth.h"
#endif

class FUltimateMobileKit;

/** Sets the email address for the user */
class FFirebaseAuthUpdateEmail : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAuthUpdateEmail(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthUpdateEmailCompleteDelegate& InDelegate, const FString& InEmail);

	virtual FString ToString() const override { return TEXT("FirebaseAuthUpdateEmail"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthUpdateEmailCompleteDelegate Delegate;
	const FString Email;
	EFirebaseAuthError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FFirebaseNativeAuthPtr NativeAuth;
	firebase::Future<void> FetchFutureResult;
#endif
};
