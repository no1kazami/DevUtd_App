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

/** Returns a stable identifier that uniquely identifies the app instance. */
class FFirebaseInstanceIdGetId : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseInstanceIdGetId(FUltimateMobileKit* InSubsystem, const FOnFirebaseInstanceIdGetIdCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseInstanceIdGetId"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseInstanceIdGetIdCompleteDelegate Delegate;
	FString ResultId;
	EFirebaseInstanceIdError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	FFirebaseNativeInstanceIdPtr NativeInstanceId;
	firebase::Future<std::string> FetchFutureResult;
#endif
};
