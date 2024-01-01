// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseAuthDelegates.h"

class FUltimateMobileKit;

/** Asynchronously logs into Google and Google Play system */
class FFirebaseAuthSignInWithGoogle : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAuthSignInWithGoogle(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthSignInWithGoogleCompleteDelegate& InDelegate);

	virtual FString ToString() const override { return TEXT("FirebaseAuthSignInWithGoogle"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

	static FString ResultIdTokenJava;
	static FString ResultServerAuthCodeJava;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthSignInWithGoogleCompleteDelegate Delegate;
	FString ResultIdToken;
	FString ResultServerAuthCode;
};
