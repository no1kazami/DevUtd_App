// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseAuthDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
#include "firebase/future.h"
#include "firebase/auth.h"
#endif

class FUltimateMobileKit;

/** Asynchronously requests the IDPs (identity providers) that can be used for the given email address */
class FFirebaseAuthFetchProvidersForEmail : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAuthFetchProvidersForEmail(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthFetchProvidersForEmailCompleteDelegate& InDelegate, const FString& InEmail);

	virtual FString ToString() const override { return TEXT("FirebaseAuthFetchProvidersForEmail"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthFetchProvidersForEmailCompleteDelegate Delegate;
	const FString Email;
	EFirebaseAuthError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FFirebaseNativeAuthPtr NativeAuth;
	firebase::Future<firebase::auth::Auth::FetchProvidersResult> FetchFutureResult;
#endif

	TArray<FString> Providers;
};
