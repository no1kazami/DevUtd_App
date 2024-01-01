// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthSignInEmailProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthSignInEmailProxySuccess, const EFirebaseAuthError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthSignInEmailProxyFailure, const EFirebaseAuthError&, Error);

/** Signs in using provided email address and password */
UCLASS(MinimalAPI)
class UFirebaseAuthSignInEmailProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthSignInEmailProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthSignInEmailProxyFailure OnFailure;

	/** Signs in using provided email address and password */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Sign In With Email And Password")
	static UFirebaseAuthSignInEmailProxy* SignInWithEmailAndPassword(const FString& Email, const FString& Password);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error);

private:
	FString Email;
	FString Password;
};
