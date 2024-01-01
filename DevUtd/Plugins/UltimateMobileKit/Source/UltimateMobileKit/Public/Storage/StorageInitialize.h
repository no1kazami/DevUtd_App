// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseStorageDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
#include "firebase/storage.h"
#include "firebase/util.h"
#endif

class FUltimateMobileKit;

/** Initialize the Firebase Storage API  */
class FFirebaseStorageInitialize : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseStorageInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseStorageInitializeCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseStorageInitialize"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseStorageInitializeCompleteDelegate Delegate;
	EFirebaseStorageError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	firebase::ModuleInitializer Initializer;
#endif
};
