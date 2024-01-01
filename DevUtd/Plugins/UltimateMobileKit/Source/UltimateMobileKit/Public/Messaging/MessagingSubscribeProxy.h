// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseMessagingDelegates.h"
#include "MessagingSubscribeProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseMessagingSubscribeProxySuccess, const EFirebaseMessagingError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseMessagingSubscribeProxyFailure, const EFirebaseMessagingError&, Error);

/** Subscribe to receive all messages to the specified topic */
UCLASS(MinimalAPI)
class UFirebaseMessagingSubscribeProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseMessagingSubscribeProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseMessagingSubscribeProxyFailure OnFailure;

	/** Subscribe to receive all messages to the specified topic */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Messaging", DisplayName = "Firebase Messaging Subscribe Topic")
	static UFirebaseMessagingSubscribeProxy* Subscribe(const FString& Topic);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseMessagingError& Error);

private:
	FString Topic;
};
