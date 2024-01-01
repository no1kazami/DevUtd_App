// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "InstanceIdLibrary.generated.h"

/** Blueprint implementation of Firebase Instance Id. Instance ID provides a unique identifier for each app instance and a mechanism to authenticate and authorize actions (for example, sending a FCM message). */
UCLASS()
class ULTIMATEMOBILEKIT_API UUltimateMobileKitInstanceId : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** Check if Firebase Instance Id is initialized */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Instance Id")
	static const bool IsFirebaseInstanceIdInitialized();
};
