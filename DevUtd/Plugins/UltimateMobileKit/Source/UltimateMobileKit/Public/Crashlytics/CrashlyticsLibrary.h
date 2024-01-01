// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CrashlyticsLibrary.generated.h"

/** Blueprint implementation of Firebase Crashlytics. Firebase Crashlytics lets diagnose problems in game with detailed reports of bugs and crashes. */
UCLASS()
class ULTIMATEMOBILEKIT_API UUltimateMobileKitCrashlytics : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** Check if Firebase Crashlytics is initialized */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Crashlytics")
	static const bool IsFirebaseCrashlyticsInitialized();

	/** The easiest way to cause a crash - great for testing! */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Crashlytics", DisplayName = "Firebase Crashlytics Force Crash")
	static void ForceCrash();

	/** The easiest way to cause an exception - great for testing! */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Crashlytics", DisplayName = "Firebase Crashlytics Force Exception")
	static void ForceException();

	/** Personalize by user identifier */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Crashlytics", DisplayName = "Firebase Crashlytics Set User Identifier")
	static void SetUserIdentifier(const FString& Identifier);

	/** Personalize by user email */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Crashlytics", DisplayName = "Firebase Crashlytics Set User Email")
	static void SetUserEmail(const FString& Email);

	/** Personalize by user name */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Crashlytics", DisplayName = "Firebase Crashlytics Set Username")
	static void SetUsername(const FString& Username);

	/** Write custom log (dev and shipping build) */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Crashlytics", DisplayName = "Firebase Crashlytics Write Log")
	static void WriteLog(const FString& Log);

	/** Write custom log with tag and priority (dev and shipping build) */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Crashlytics", DisplayName = "Firebase Crashlytics Write Log With Tag And Priority")
	static void WriteLogWithTagAndPriority(const FString& Log, const FString& Tag, const int32 Priority);

	/** Add custom key with string value */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Crashlytics", DisplayName = "Firebase Crashlytics Set String")
	static void SetString(const FString& Key, const FString& Value);

	/** Add custom key with bool value */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Crashlytics", DisplayName = "Firebase Crashlytics Set Bool")
	static void SetBool(const FString& Key, const bool Value);

	/** Add custom key with float value */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Crashlytics", DisplayName = "Firebase Crashlytics Set Float")
	static void SetFloat(const FString& Key, const float Value);

	/** Add custom key with integer value */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Crashlytics", DisplayName = "Firebase Crashlytics Set Integer")
	static void SetInteger(const FString& Key, const int32 Value);
};
