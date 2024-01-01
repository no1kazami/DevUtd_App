// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseLinksDelegates.h"
#include "Links/LinksListener.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
#include "firebase/util.h"
#endif

class FUltimateMobileKit;

/** Initialize the Firebase Dynamic Links API  */
class FFirebaseLinksInitialize : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseLinksInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseLinksInitializeCompleteDelegate& InDelegate, UFirebaseLinksListener* InListener);

	virtual FString ToString() const override { return TEXT("FirebaseLinksInitialize"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseLinksInitializeCompleteDelegate Delegate;
	UFirebaseLinksListener* Listener;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	firebase::ModuleInitializer Initializer;
#endif
};
