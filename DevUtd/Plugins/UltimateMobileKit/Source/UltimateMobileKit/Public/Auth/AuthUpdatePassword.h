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

/*
* Attempts to change the password for the current user.
* For an account linked to an Identity Provider (IDP) with no password, this will result in the account becoming an email/password-based account while maintaining the IDP link. May fail if the password is invalid, if there is a conflicting email/password-based account, or if the token has expired. To retrieve fresh tokens, call Reauthenticate.
*/
class FFirebaseAuthUpdatePassword : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAuthUpdatePassword(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthUpdatePasswordCompleteDelegate& InDelegate, const FString& InPassword);

	virtual FString ToString() const override { return TEXT("FirebaseAuthUpdatePassword"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthUpdatePasswordCompleteDelegate Delegate;
	const FString Password;
	EFirebaseAuthError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FFirebaseNativeAuthPtr NativeAuth;
	firebase::Future<void> FetchFutureResult;
#endif
};
