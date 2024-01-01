// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseMessagingDelegates.h"
#include "MessagingRequestPermissionProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseMessagingRequestPermissionProxySuccess, const EFirebaseMessagingError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseMessagingRequestPermissionProxyFailure, const EFirebaseMessagingError&, Error);

/** Displays a prompt to the user requesting permission to display notifications. */
UCLASS(MinimalAPI)
class UFirebaseMessagingRequestPermissionProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseMessagingRequestPermissionProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseMessagingRequestPermissionProxyFailure OnFailure;

	/** Displays a prompt to the user requesting permission to display notifications. */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Messaging", DisplayName = "Firebase Messaging Request Permission")
	static UFirebaseMessagingRequestPermissionProxy* RequestPermission();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseMessagingError& Error);
};
