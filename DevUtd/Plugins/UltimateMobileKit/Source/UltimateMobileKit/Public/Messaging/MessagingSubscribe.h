// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseMessagingDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
#include "firebase/future.h"
#include "firebase/messaging.h"
#endif

class FUltimateMobileKit;

/** Subscribe to receive all messages to the specified topic */
class FFirebaseMessagingSubscribe : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseMessagingSubscribe(FUltimateMobileKit* InSubsystem, const FOnFirebaseMessagingSubscribeCompleteDelegate& InDelegate, const FString& Topic);

	virtual FString ToString() const override { return TEXT("FirebaseMessagingSubscribe"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseMessagingSubscribeCompleteDelegate Delegate;
	const FString Topic;
	EFirebaseMessagingError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	firebase::Future<void> FetchFutureResult;
#endif
};
