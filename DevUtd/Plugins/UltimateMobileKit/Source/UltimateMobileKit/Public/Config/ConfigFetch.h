// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseConfigDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
#include "firebase/future.h"
#endif

class FUltimateMobileKit;

/** Fetches config data from the server */
class FFirebaseConfigFetch : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseConfigFetch(FUltimateMobileKit* InSubsystem, const FOnFirebaseConfigFetchCompleteDelegate& InDelegate, const int32 InCacheExpirationInSeconds);

	virtual FString ToString() const override { return TEXT("FirebaseRemoteConfigFetch"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	FOnFirebaseConfigFetchCompleteDelegate Delegate;
	int32 CacheExpirationInSeconds;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	firebase::Future<void> FetchFutureResult;
#endif
};
