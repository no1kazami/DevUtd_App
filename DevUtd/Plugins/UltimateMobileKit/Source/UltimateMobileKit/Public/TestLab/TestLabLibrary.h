// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestLabLibrary.generated.h"

/** Blueprint implementation of Firebase TestLab. Firebase TestLab lets diagnose problems in game with detailed reports of bugs and crashes. */
UCLASS()
class ULTIMATEMOBILEKIT_API UUltimateMobileKitTestLab : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** Check if Firebase Test Lab is initialized */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Test Lab")
	static const bool IsFirebaseTestLabInitialized();

	/** Make a screenshot for Firebase Test Lab */
	UFUNCTION(BlueprintCallable, BlueprintCallable, Category = "Ultimate Mobile Kit|Test Lab", DisplayName = "Firebase Test Lab Take Screenshot")
	static void TakeScreenshot(const FString& Label);

	/** Finishes test of Firebase Test Lab */
	UFUNCTION(BlueprintCallable, BlueprintCallable, Category = "Ultimate Mobile Kit|Test Lab", DisplayName = "Firebase Test Lab Finish Test")
	static void FinishTest();

	/** Gets game loop scenario of Firebase Test Lab */
	UFUNCTION(BlueprintCallable, BlueprintCallable, Category = "Ultimate Mobile Kit|Test Lab", DisplayName = "Firebase Test Lab Get Game Loop Scenario")
	static int32 GetGameLoopScenario();
};
