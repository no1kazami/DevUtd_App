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

/** Displays a prompt to the user requesting permission to display notifications. */
class FFirebaseMessagingRequestPermission : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseMessagingRequestPermission(FUltimateMobileKit* InSubsystem, const FOnFirebaseMessagingRequestPermissionCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseMessagingRequestPermission"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseMessagingRequestPermissionCompleteDelegate Delegate;
	EFirebaseMessagingError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	firebase::Future<void> FetchFutureResult;
#endif
};
