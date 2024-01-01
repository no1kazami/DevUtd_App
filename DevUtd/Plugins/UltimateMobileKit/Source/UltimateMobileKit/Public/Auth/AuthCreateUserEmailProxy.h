// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthCreateUserEmailProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthCreateUserEmailProxySuccess, const EFirebaseAuthError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthCreateUserEmailProxyFailure, const EFirebaseAuthError&, Error);

/** Creates, and on success, logs in a user with the given email address and password */
UCLASS(MinimalAPI)
class UFirebaseAuthCreateUserEmailProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthCreateUserEmailProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthCreateUserEmailProxyFailure OnFailure;

	/** Creates, and on success, logs in a user with the given email address and password */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Create User With Email And Password")
	static UFirebaseAuthCreateUserEmailProxy* CreateUserWithEmailAndPassword(const FString& Email, const FString& Password);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error);

private:
	FString Email;
	FString Password;
};
