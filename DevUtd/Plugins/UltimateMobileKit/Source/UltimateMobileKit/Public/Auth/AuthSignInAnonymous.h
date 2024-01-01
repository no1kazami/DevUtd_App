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

/**
* Asynchronously creates and becomes an anonymous user.
* If there is already an anonymous user signed in, that user will be returned instead. If there is any other existing user, that user will be signed out.
*/
class FFirebaseAuthSignInAnonymous : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAuthSignInAnonymous(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthSignInAnonymousCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseAuthSignInAnonymous"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthSignInAnonymousCompleteDelegate Delegate;
	EFirebaseAuthError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FFirebaseNativeAuthPtr NativeAuth;
	firebase::Future<firebase::auth::User*> FetchFutureResult;
#endif
};
