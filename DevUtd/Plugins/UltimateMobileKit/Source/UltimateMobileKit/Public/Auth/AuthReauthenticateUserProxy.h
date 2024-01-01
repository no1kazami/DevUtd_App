// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthReauthenticateUserProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthReauthenticateUserProxySuccess, const EFirebaseAuthError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthReauthenticateUserProxyFailure, const EFirebaseAuthError&, Error);

/** Reauthenticate using a credential */
UCLASS(MinimalAPI)
class UFirebaseAuthReauthenticateUserProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthReauthenticateUserProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthReauthenticateUserProxyFailure OnFailure;

	/** Reauthenticate using a credential */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Reauthenticate User")
	static UFirebaseAuthReauthenticateUserProxy* ReauthenticateUser(const UFirebaseCredential* Credential);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error);

private:
	const UFirebaseCredential* Credential;
};
