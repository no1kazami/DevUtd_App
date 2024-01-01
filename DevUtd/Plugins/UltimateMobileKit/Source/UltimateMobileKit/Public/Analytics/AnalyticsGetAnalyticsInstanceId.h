// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseAnalyticsDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
#include "firebase/future.h"
#include "firebase/analytics.h"
#endif

class FUltimateMobileKit;

/** Get the instance ID from the analytics service. */
class FFirebaseAnalyticsGetAnalyticsInstanceId : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAnalyticsGetAnalyticsInstanceId(FUltimateMobileKit* InSubsystem, const FOnFirebaseAnalyticsGetAnalyticsInstanceIdCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseAnalyticsGetAnalyticsInstanceId"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAnalyticsGetAnalyticsInstanceIdCompleteDelegate Delegate;
	FString ResultInstanceId;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
	firebase::Future<std::string> FetchFutureResult;
#endif
};
