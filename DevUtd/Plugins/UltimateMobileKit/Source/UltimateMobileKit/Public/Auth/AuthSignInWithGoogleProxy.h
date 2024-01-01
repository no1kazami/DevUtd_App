// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthSignInWithGoogleProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFirebaseAuthSignInWithGoogleProxySuccess, const FString&, IdToken, const FString&, ServerAuthCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFirebaseAuthSignInWithGoogleProxyFailure);

/** Asynchronously logs into Google and Google Play system */
UCLASS(MinimalAPI)
class UFirebaseAuthSignInWithGoogleProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthSignInWithGoogleProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthSignInWithGoogleProxyFailure OnFailure;

	/** Asynchronously logs into Google and Google Play system */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Sign In With Google")
	static UFirebaseAuthSignInWithGoogleProxy* SignInWithGoogle();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const FString& IdToken, const FString& ServerAuthCode);
};
