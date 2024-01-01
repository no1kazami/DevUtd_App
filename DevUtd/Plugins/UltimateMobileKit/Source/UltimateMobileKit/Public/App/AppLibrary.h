// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Delegates/FirebaseAppDelegates.h"
#include "AppLibrary.generated.h"

/** Blueprint implementation of FirebaseApp. Initialization and management of Firebase application. Entry point for other modules. */
UCLASS()
class ULTIMATEMOBILEKIT_API UUltimateMobileKitApp : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** Check if Firebase is initialized */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|App")
	static const bool IsFirebaseInitialized();

	/** Check whether Google Play services is available on this device. */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|App", DisplayName = "Firebase Check Google Play Availability")
	static const EGooglePlayAvailability CheckGooglePlayAvailability();
};
