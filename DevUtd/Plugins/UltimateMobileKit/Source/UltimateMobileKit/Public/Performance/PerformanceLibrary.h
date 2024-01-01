// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "PerformanceLibrary.generated.h"

UCLASS()
class ULTIMATEMOBILEKIT_API UUltimateMobileKitPerformance : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** Check if Firebase Performance Monitoring is initialized */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Performance Monitoring")
	static const bool IsFirebasePerformanceInitialized();
};
