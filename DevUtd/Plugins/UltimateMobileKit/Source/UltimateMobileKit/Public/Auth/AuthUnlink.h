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

/** Unlinks the current user from the provider specified */
class FFirebaseAuthUnlink : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAuthUnlink(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthUnlinkCompleteDelegate& InDelegate, const EFirebaseProvider InProvider);

	virtual FString ToString() const override { return TEXT("FirebaseAuthUnlink"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthUnlinkCompleteDelegate Delegate;
	const EFirebaseProvider Provider;
	EFirebaseAuthError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FFirebaseNativeAuthPtr NativeAuth;
	firebase::Future<firebase::auth::User*> FetchFutureResult;
#endif
};
