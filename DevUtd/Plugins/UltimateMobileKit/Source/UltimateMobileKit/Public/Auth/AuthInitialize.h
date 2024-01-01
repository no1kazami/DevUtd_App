// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseAuthDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
#include "firebase/util.h"
#endif

class FUltimateMobileKit;

/** Initialize the Firebase Authentication API  */
class FFirebaseAuthInitialize : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAuthInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthInitializeCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseAuthInitialize"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthInitializeCompleteDelegate Delegate;
	EFirebaseAuthError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	firebase::ModuleInitializer Initializer;
#endif
};
