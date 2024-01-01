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

/** Delete the ID associated with the app, revoke all tokens and allocate a new ID. */
class FFirebaseInstanceIdDeleteId : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseInstanceIdDeleteId(FUltimateMobileKit* InSubsystem, const FOnFirebaseInstanceIdDeleteIdCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseInstanceIdDeleteId"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseInstanceIdDeleteIdCompleteDelegate Delegate;
	EFirebaseInstanceIdError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	FFirebaseNativeInstanceIdPtr NativeInstanceId;
	firebase::Future<void> FetchFutureResult;
#endif
};
