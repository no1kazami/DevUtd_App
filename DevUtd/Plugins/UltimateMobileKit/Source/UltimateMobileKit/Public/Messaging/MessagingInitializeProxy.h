// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "MessagingInitializeProxy.generated.h"

/** Initialize the Firebase Messaging API  */
UCLASS(MinimalAPI)
class UFirebaseMessagingInitializeProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	/** Initialize the Firebase Messaging API  */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Messaging", DisplayName = "Firebase Messaging Init")
	static UFirebaseMessagingInitializeProxy* Init(bool RequestPermission = true);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess);

private:
	bool RequestPermission = true;
};
