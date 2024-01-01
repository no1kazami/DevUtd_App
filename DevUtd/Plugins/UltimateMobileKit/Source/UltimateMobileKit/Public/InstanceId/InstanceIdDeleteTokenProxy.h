// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseInstanceIdDelegates.h"
#include "InstanceIdDeleteTokenProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseInstanceIdDeleteTokenSuccess, const EFirebaseInstanceIdError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseInstanceIdDeleteTokenFailure, const EFirebaseInstanceIdError&, Error);

/** Revokes access to a scope (action) */
UCLASS(MinimalAPI)
class UFirebaseInstanceIdDeleteTokenProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseInstanceIdDeleteTokenSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseInstanceIdDeleteTokenFailure OnFailure;

	/** Revokes access to a scope (action) */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Instance Id", DisplayName = "Firebase Instance Id Delete Token")
	static UFirebaseInstanceIdDeleteTokenProxy* DeleteToken();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseInstanceIdError& Error);
};
