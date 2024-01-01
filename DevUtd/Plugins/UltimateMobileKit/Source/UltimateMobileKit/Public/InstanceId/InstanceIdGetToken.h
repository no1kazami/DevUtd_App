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

/** Returns a token that authorizes an Entity to perform an action on behalf of the application identified by Instance ID. */
class FFirebaseInstanceIdGetToken : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseInstanceIdGetToken(FUltimateMobileKit* InSubsystem, const FOnFirebaseInstanceIdGetTokenCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseInstanceIdGetToken"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseInstanceIdGetTokenCompleteDelegate Delegate;
	FString ResultToken;
	EFirebaseInstanceIdError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	FFirebaseNativeInstanceIdPtr NativeInstanceId;
	firebase::Future<std::string> FetchFutureResult;
#endif
};
