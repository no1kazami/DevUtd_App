// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseConfigDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
#include "firebase/util.h"
#endif

class FUltimateMobileKit;

/** Initialize the Firebase Config API  */
class FFirebaseConfigInitialize : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseConfigInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseConfigInitializeCompleteDelegate& InDelegate, const TArray<UFirebaseVariant*> InDefaultParameters, const FString& InConfigNamespace = FString());

	virtual FString ToString() const override { return TEXT("FirebaseConfigInitialize"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	FOnFirebaseConfigInitializeCompleteDelegate Delegate;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	firebase::ModuleInitializer Initializer;
#endif

	const TArray<UFirebaseVariant*> DefaultParameters;
	const FString ConfigNamespace;
};
