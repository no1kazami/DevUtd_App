// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "FirebaseCredential.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthSignInWithCredentialProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthSignInWithCredentialProxySuccess, const EFirebaseAuthError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthSignInWithCredentialProxyFailure, const EFirebaseAuthError&, Error);

/** Asynchronously logs into Firebase with the given credentials */
UCLASS(MinimalAPI)
class UFirebaseAuthSignInWithCredentialProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthSignInWithCredentialProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthSignInWithCredentialProxyFailure OnFailure;

	/** Asynchronously logs into Firebase with the given credentials */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Sign In With Credential")
	static UFirebaseAuthSignInWithCredentialProxy* SignInWithCredential(const UFirebaseCredential* Credential);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error);

private:
	const UFirebaseCredential* Credential;
};
