// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthSignInWithCustomTokenProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthSignInWithCustomTokenProxySuccess, const EFirebaseAuthError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthSignInWithCustomTokenProxyFailure, const EFirebaseAuthError&, Error);

/** Asynchronously logs into Firebase with the given Auth token */
UCLASS(MinimalAPI)
class UFirebaseAuthSignInWithCustomTokenProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthSignInWithCustomTokenProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthSignInWithCustomTokenProxyFailure OnFailure;

	/** Asynchronously logs into Firebase with the given Auth token */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Sign In With Custom Token")
	static UFirebaseAuthSignInWithCustomTokenProxy* SignInWithCustomToken(const FString& Token);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error);

private:
	FString Token;
};
