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

/** Asynchronously logs into Firebase with the given credentials */
class FFirebaseAuthSignInWithCredential : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAuthSignInWithCredential(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthSignInWithCredentialCompleteDelegate& InDelegate, const UFirebaseCredential* InCredential);

	virtual FString ToString() const override { return TEXT("FirebaseAuthSignInWithCredential"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthSignInWithCredentialCompleteDelegate Delegate;
	const UFirebaseCredential* Credential;
	EFirebaseAuthError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FFirebaseNativeAuthPtr NativeAuth;
	firebase::Future<firebase::auth::User*> FetchFutureResult;
#endif
};
