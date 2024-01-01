// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "UltimateMobileKit.h"
#include "FirebaseVariant.h"
#include "AnalyticsLibrary.generated.h"

/** Blueprint implementation of FirebaseAnalytics. Firebase Analytics provides insight on game usage and player engagement. This class allows to log events and screens. */
UCLASS()
class ULTIMATEMOBILEKIT_API UUltimateMobileKitAnalytics : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** Check if Firebase Analytics is initialized */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Analytics")
	static const bool IsFirebaseAnalyticsInitialized();

	/** Log an event with one or more parameters */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Analytics", DisplayName = "Firebase Analytics Log Event", meta = (AutoCreateRefTerm = "Parameters"))
	static void LogEvent(const FString& Name, const TArray<UFirebaseVariant*> Parameters);

	/** Log an event with one string parameter */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Analytics", DisplayName = "Firebase Analytics Log Event String")
	static void LogEventString(const FString& Name, const FString& ParameterName, const FString& ParameterValue);

	/** Log an event with one integer parameter */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Analytics", DisplayName = "Firebase Analytics Log Event Integer")
	static void LogEventInteger(const FString& Name, const FString& ParameterName, const int32 ParameterValue);

	/** Log an event with one float parameter */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Analytics", DisplayName = "Firebase Analytics Log Event Double")
	static void LogEventFloat(const FString& Name, const FString& ParameterName, const float ParameterValue);

	/** Sets the user ID property */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Analytics", DisplayName = "Firebase Analytics Set User Id")
	static void SetUserId(const FString& UserId);

	/** Set a user property to the given value */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Analytics", DisplayName = "Firebase Analytics Set User Property")
	static void SetUserProperty(const FString& Name, const FString& Property);

	/** Sets the current screen name and screen class, which specifies the current visual context in your app */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Analytics", DisplayName = "Firebase Analytics Set Current Screen")
	static void SetCurrentScreen(const FString& ScreenName, const FString& ScreenClass);

	/** Clears all analytics data for this app from the device and resets the app instance id. */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Analytics", DisplayName = "Firebase Analytics Reset Analytics Data")
	static void ResetAnalyticsData();

	/** Sets whether analytics collection is enabled for this app on this device. This setting is persisted across app sessions. By default it is enabled. */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Analytics", DisplayName = "Firebase Analytics Set Analytics Collection Enabled")
	static void SetAnalyticsCollectionEnabled(bool bEnabled);
};
