// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseInstanceIdDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
#include "firebase/future.h"
#include "firebase/instance_id.h"
#endif

class FUltimateMobileKit;

/** Revokes access to a scope (action) */
class FFirebaseInstanceIdDeleteToken : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseInstanceIdDeleteToken(FUltimateMobileKit* InSubsystem, const FOnFirebaseInstanceIdDeleteTokenCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseInstanceIdDeleteToken"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseInstanceIdDeleteTokenCompleteDelegate Delegate;
	EFirebaseInstanceIdError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	FFirebaseNativeInstanceIdPtr NativeInstanceId;
	firebase::Future<void> FetchFutureResult;
#endif
};
