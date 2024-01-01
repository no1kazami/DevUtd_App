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

/** The Java Web Token (JWT) that can be used to identify the user to the backend */
class FFirebaseAuthGetUserToken : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAuthGetUserToken(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthGetUserTokenCompleteDelegate& InDelegate, const bool InForceRefresh = false);

	virtual FString ToString() const override { return TEXT("FirebaseAuthGetUserToken"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthGetUserTokenCompleteDelegate Delegate;
	bool ForceRefresh;
	FString ResultToken;
	EFirebaseAuthError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FFirebaseNativeAuthPtr NativeAuth;
	firebase::Future<std::string> FetchFutureResult;
#endif
};