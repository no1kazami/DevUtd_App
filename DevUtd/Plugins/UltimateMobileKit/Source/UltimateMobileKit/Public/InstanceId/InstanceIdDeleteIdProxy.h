// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseInstanceIdDelegates.h"
#include "InstanceIdDeleteIdProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseInstanceIdDeleteIdSuccess, const EFirebaseInstanceIdError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseInstanceIdDeleteIdFailure, const EFirebaseInstanceIdError&, Error);

/** Delete the ID associated with the app, revoke all tokens and allocate a new ID. */
UCLASS(MinimalAPI)
class UFirebaseInstanceIdDeleteIdProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseInstanceIdDeleteIdSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseInstanceIdDeleteIdFailure OnFailure;

	/** Delete the ID associated with the app, revoke all tokens and allocate a new ID. */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Instance Id", DisplayName = "Firebase Instance Id Delete Id")
	static UFirebaseInstanceIdDeleteIdProxy* DeleteId();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseInstanceIdError& Error);
};
