// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseMessagingDelegates.h"
#include "MessagingUnsubscribeProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseMessagingUnsubscribeProxySuccess, const EFirebaseMessagingError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseMessagingUnsubscribeProxyFailure, const EFirebaseMessagingError&, Error);

/** Unsubscribe from a topic */
UCLASS(MinimalAPI)
class UFirebaseMessagingUnsubscribeProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseMessagingUnsubscribeProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseMessagingUnsubscribeProxyFailure OnFailure;

	/** Unsubscribe from a topic */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Messaging", DisplayName = "Firebase Messaging Unsubscribe Topic")
	static UFirebaseMessagingUnsubscribeProxy* Unsubscribe(const FString& Topic);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseMessagingError& Error);

private:
	FString Topic;
};
