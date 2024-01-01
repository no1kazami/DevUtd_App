// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthVerifyPhoneNumberProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FFirebaseAuthVerifyPhoneNumberSuccess, const EFirebaseAuthError&, Error, const FString&, VerificationId, const UFirebaseCredential*, Credential);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthVerifyPhoneNumberFailure, const EFirebaseAuthError&, Error);

/** Start the phone number authentication operation. */
UCLASS(MinimalAPI)
class UFirebaseAuthVerifyPhoneNumberProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthVerifyPhoneNumberSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthVerifyPhoneNumberFailure OnFailure;

	/** Start the phone number authentication operation. */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Verify Phone Number")
	static UFirebaseAuthVerifyPhoneNumberProxy* VerifyPhoneNumber(const FString& PhoneNumber);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error, const FString& VerificationId, const UFirebaseCredential* Credential);

private:
	FString PhoneNumber;
};
