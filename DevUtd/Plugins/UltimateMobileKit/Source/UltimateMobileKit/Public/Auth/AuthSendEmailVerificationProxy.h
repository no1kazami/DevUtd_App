// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthSendEmailVerificationProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthSendEmailVerificationProxySuccess, const EFirebaseAuthError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthSendEmailVerificationProxyFailure, const EFirebaseAuthError&, Error);

/** Initiates email verification for the user */
UCLASS(MinimalAPI)
class UFirebaseAuthSendEmailVerificationProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthSendEmailVerificationProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthSendEmailVerificationProxyFailure OnFailure;

	/** Initiates email verification for the user */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Send Email Verification")
	static UFirebaseAuthSendEmailVerificationProxy* SendEmailVerification();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error);
};
