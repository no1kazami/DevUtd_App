// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthDeleteUserProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthDeleteProxySuccess, const EFirebaseAuthError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthDeleteProxyFailure, const EFirebaseAuthError&, Error);

/** Deletes the user account */
UCLASS(MinimalAPI)
class UFirebaseAuthDeleteUserProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthDeleteProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthDeleteProxyFailure OnFailure;

	/** Deletes the user account */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Delete User")
	static UFirebaseAuthDeleteUserProxy* DeleteUser();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error);
};
