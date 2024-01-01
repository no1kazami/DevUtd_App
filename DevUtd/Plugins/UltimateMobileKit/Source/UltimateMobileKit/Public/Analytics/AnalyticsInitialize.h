// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseAnalyticsDelegates.h"

#if WITH_ULTIMATEMOBILEKIT
#include "firebase/util.h"
#endif

class FUltimateMobileKit;

/** Initialize the Firebase Analytics API  */
class FFirebaseAnalyticsInitialize : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAnalyticsInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseAnalyticsInitializeCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseAnalyticsInitialize"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAnalyticsInitializeCompleteDelegate Delegate;
};
