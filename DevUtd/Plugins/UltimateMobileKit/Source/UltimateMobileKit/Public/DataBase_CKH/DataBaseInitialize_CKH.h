// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseDatabaseDelegates_CKH.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
#include "firebase/util.h"
#endif

class FUltimateMobileKit;

class FFirebaseDataBaseInitialize_CKH : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseDataBaseInitialize_CKH( FUltimateMobileKit* InSubsystem, const FOnFirebaseDataBaseInitializeCompleteDelegate& InDelegate );

	virtual FString ToString() const override { return TEXT( "FirebaseDataBaseInitialize" ); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	FOnFirebaseDataBaseInitializeCompleteDelegate Delegate;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	firebase::ModuleInitializer Initializer;
#endif
};
