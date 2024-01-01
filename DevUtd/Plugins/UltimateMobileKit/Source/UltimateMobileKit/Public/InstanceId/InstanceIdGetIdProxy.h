// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseInstanceIdDelegates.h"
#include "InstanceIdGetIdProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFirebaseInstanceIdGetIdSuccess, const FString&, Id, const EFirebaseInstanceIdError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseInstanceIdGetIdFailure, const EFirebaseInstanceIdError&, Error);

/** Returns a stable identifier that uniquely identifies the app instance. */
UCLASS(MinimalAPI)
class UFirebaseInstanceIdGetIdProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseInstanceIdGetIdSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseInstanceIdGetIdFailure OnFailure;

	/** Returns a stable identifier that uniquely identifies the app instance. */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Instance Id", DisplayName = "Firebase Instance Id Get Id")
	static UFirebaseInstanceIdGetIdProxy* GetId();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseInstanceIdError& Error, const FString& Id);
};
