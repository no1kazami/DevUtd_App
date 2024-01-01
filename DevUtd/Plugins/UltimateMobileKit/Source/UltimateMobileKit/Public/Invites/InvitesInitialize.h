// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
#include "firebase/util.h"
#endif

class FUltimateMobileKit;

/** Initialize the Firebase Invites API  */
class FFirebaseInvitesInitialize : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseInvitesInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseInvitesInitializeCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseInvitesInitialize"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseInvitesInitializeCompleteDelegate Delegate;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	firebase::ModuleInitializer Initializer;
#endif
};
