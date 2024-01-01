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

/** Reauthenticate using a credential */
class FFirebaseAuthReauthenticateUser : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAuthReauthenticateUser(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthReauthenticateUserCompleteDelegate& InDelegate, const UFirebaseCredential* InCredential);

	virtual FString ToString() const override { return TEXT("FirebaseAuthReauthenticateUser"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthReauthenticateUserCompleteDelegate Delegate;
	EFirebaseAuthError Error;
	const UFirebaseCredential* Credential;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FFirebaseNativeAuthPtr NativeAuth;
	firebase::Future<void> FetchFutureResult;
#endif
};
