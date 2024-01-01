// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseInAppMessagingDelegates.h"

class FUltimateMobileKit;

/** Initialize the Firebase In-App Messaging API  */
class FFirebaseInAppMessagingInitialize : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseInAppMessagingInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseInAppMessagingInitializeCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseInAppMessagingInitialize"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseInAppMessagingInitializeCompleteDelegate Delegate;
};
