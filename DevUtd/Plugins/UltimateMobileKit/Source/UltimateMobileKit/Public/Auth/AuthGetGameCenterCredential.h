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

/** Retrieves Game Center Credential for Game Center Sign In */
class FFirebaseAuthGetGameCenterCredential : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAuthGetGameCenterCredential(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthGetGameCenterCredentialCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseAuthGetGameCenterCredential"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthGetGameCenterCredentialCompleteDelegate Delegate;
	UFirebaseCredential* ResultCredential;
	EFirebaseAuthError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FFirebaseNativeAuthPtr NativeAuth;
	firebase::Future<firebase::auth::Credential> FetchFutureResult;
#endif
};
