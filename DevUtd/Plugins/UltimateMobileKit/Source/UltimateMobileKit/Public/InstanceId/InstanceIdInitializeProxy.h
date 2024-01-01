// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseInstanceIdDelegates.h"
#include "InstanceIdInitializeProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseInstanceIdInitializeSuccess, const EFirebaseInstanceIdError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseInstanceIdInitializeFailure, const EFirebaseInstanceIdError&, Error);

/** Initialize the Firebase Instance Id API  */
UCLASS(MinimalAPI)
class UFirebaseInstanceIdInitializeProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseInstanceIdInitializeSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseInstanceIdInitializeFailure OnFailure;

	/** Initialize the Firebase Instance Id API  */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Instance Id", DisplayName = "Firebase Instance Id Init")
	static UFirebaseInstanceIdInitializeProxy* Init();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseInstanceIdError& Error);
};
