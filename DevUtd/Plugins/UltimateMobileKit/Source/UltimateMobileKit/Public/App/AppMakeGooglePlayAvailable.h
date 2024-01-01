// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseAppDelegates.h"

#if WITH_ULTIMATEMOBILEKIT
#include "firebase/future.h"
#include "google_play_services/availability.h"
#endif

class FUltimateMobileKit;

/** Attempt to make Google Play services available, by installing, updating, activating, or whatever else needs to be done. */
class FFirebaseAppMakeGooglePlayAvailable : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAppMakeGooglePlayAvailable(FUltimateMobileKit* InSubsystem, const FOnFirebaseMakeGooglePlayAvailableCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseAppMakeGooglePlayAvailable"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseMakeGooglePlayAvailableCompleteDelegate Delegate;

#if WITH_ULTIMATEMOBILEKIT
	FFirebaseNativeAppPtr NativeApp;
	firebase::Future<void> FetchFutureResult;
#endif
};
