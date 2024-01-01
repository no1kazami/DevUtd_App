// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthGetGameCenterCredentialProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFirebaseAuthGetGameCenterCredentialProxySuccess, const EFirebaseAuthError&, Error, const UFirebaseCredential*, Credential);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthGetGameCenterCredentialProxyFailure, const EFirebaseAuthError&, Error);

/** Retrieves Game Center Credential for Game Center Sign In */
UCLASS(MinimalAPI)
class UFirebaseAuthGetGameCenterCredentialProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthGetGameCenterCredentialProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthGetGameCenterCredentialProxyFailure OnFailure;

	/** Retrieves Game Center Credential for Game Center Sign In */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Game Center Credential")
	static UFirebaseAuthGetGameCenterCredentialProxy* GameCenterCredential();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error, const UFirebaseCredential* Credential);
};
