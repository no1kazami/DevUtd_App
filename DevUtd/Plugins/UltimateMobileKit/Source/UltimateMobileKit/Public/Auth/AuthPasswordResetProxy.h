// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthPasswordResetProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthPasswordResetProxySuccess, const EFirebaseAuthError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthPasswordResetProxyFailure, const EFirebaseAuthError&, Error);

/** Initiates a password reset for the given email address */
UCLASS(MinimalAPI)
class UFirebaseAuthPasswordResetProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthPasswordResetProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthPasswordResetProxyFailure OnFailure;

	/** Initiates a password reset for the given email address */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Send Password Reset Email")
	static UFirebaseAuthPasswordResetProxy* SendPasswordResetEmail(const FString& Email);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error);

private:
	FString Email;
};
