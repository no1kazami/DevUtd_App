// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseInstanceIdDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
#include "firebase/instance_id.h"
#include "firebase/util.h"
#endif

class FUltimateMobileKit;

/** Initialize the Firebase Instance Id API  */
class FFirebaseInstanceIdInitialize : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseInstanceIdInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseInstanceIdInitializeCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseInstanceIdInitialize"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseInstanceIdInitializeCompleteDelegate Delegate;
	EFirebaseInstanceIdError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	firebase::ModuleInitializer Initializer;
#endif
};
