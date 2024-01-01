// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseMessagingDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
#include "firebase/util.h"
#include "firebase/messaging.h"
#endif

class FUltimateMobileKit;

/** Initialize the Firebase Messaging API  */
class FFirebaseMessagingInitialize : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseMessagingInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseMessagingInitializeCompleteDelegate& InDelegate, bool InRequestPermission, const FFirebaseMessaging* InFirebaseMessaging);

	virtual FString ToString() const override { return TEXT("FirebaseMessagingInitialize"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseMessagingInitializeCompleteDelegate Delegate;
	bool RequestPermission = true;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	firebase::ModuleInitializer Initializer;
#endif

public:
	const FFirebaseMessaging* FirebaseMessaging;
};
