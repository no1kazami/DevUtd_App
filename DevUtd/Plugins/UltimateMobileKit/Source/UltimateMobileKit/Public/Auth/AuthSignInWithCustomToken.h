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

/** Asynchronously logs into Firebase with the given Auth token */
class FFirebaseAuthSignInWithCustomToken : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAuthSignInWithCustomToken(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthSignInWithCustomTokenCompleteDelegate& InDelegate, const FString& InToken);

	virtual FString ToString() const override { return TEXT("FirebaseAuthSignInWithCustomToken"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthSignInWithCustomTokenCompleteDelegate Delegate;
	const FString Token;
	EFirebaseAuthError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FFirebaseNativeAuthPtr NativeAuth;
	firebase::Future<firebase::auth::User*> FetchFutureResult;
#endif
};
