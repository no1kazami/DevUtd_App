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

/** Signs in using provided email address and password */
class FFirebaseAuthSignInEmail : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAuthSignInEmail(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthSignInEmailCompleteDelegate& InDelegate, const FString& InEmail, const FString& InPassword);

	virtual FString ToString() const override { return TEXT("FirebaseAuthSignInEmail"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthSignInEmailCompleteDelegate Delegate;
	const FString Email;
	const FString Password;
	EFirebaseAuthError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FFirebaseNativeAuthPtr NativeAuth;
	firebase::Future<firebase::auth::User*> FetchFutureResult;
#endif
};
