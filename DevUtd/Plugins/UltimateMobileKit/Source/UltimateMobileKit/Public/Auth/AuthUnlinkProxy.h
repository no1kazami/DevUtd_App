// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthUnlinkProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthUnlinkProxySuccess, const EFirebaseAuthError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthUnlinkProxyFailure, const EFirebaseAuthError&, Error);

/** Unlinks the current user from the provider specified */
UCLASS(MinimalAPI)
class UFirebaseAuthUnlinkProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthUnlinkProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthUnlinkProxyFailure OnFailure;

	/** Unlinks the current user from the provider specified */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Unlink Provider")
	static UFirebaseAuthUnlinkProxy* Unlink(const EFirebaseProvider Provider);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error);

private:
	EFirebaseProvider Provider;
};
