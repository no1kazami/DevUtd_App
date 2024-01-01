// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "FirebaseVariant.h"
#include "Delegates/FirebaseAnalyticsDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
#include "firebase/analytics.h"
#endif

/** Firebase Analytics provides insight on game usage and player engagement. This class allows to log events and screens. */
class ULTIMATEMOBILEKIT_API FFirebaseAnalytics
{
public:
	FFirebaseAnalytics();
	virtual ~FFirebaseAnalytics();

	/** Initialize the Firebase Analytics API  */
	void Init(const FOnFirebaseAnalyticsInitializeCompleteDelegate& Delegate = FOnFirebaseAnalyticsInitializeCompleteDelegate());

	/** Shutdown the Firebase Analytics API  */
	void Shutdown();

	/** Check if Firebase Analytics is initialized */
	const bool IsInitialized() const;

	/** Set Firebase Authentication initialization state */
	void SetInitialized(const bool Initialized);

	/** Log an event with one or more parameters */
	void LogEvent(const FString& Name, const TArray<UFirebaseVariant*> Parameters) const;

	/** Log an event with one string parameter */
	void LogEventString(const FString& Name, const FString& ParameterName, const FString& ParameterValue) const;

	/** Log an event with one integer parameter */
	void LogEventInteger(const FString& Name, const FString& ParameterName, const int32 ParameterValue) const;

	/** Log an event with one float parameter */
	void LogEventFloat(const FString& Name, const FString& ParameterName, const float ParameterValue) const;

	/** Sets the user ID property */
	void SetUserId(const FString& UserId) const;

	/** Set a user property to the given value */
	void SetUserProperty(const FString& Name, const FString& Property) const;

	/** Sets the current screen name and screen class, which specifies the current visual context in your app */
	void SetCurrentScreen(const FString& ScreenName, const FString& ScreenClass) const;

	/** Clears all analytics data for this app from the device and resets the app instance id. */
	void ResetAnalyticsData() const;

	/** Sets whether analytics collection is enabled for this app on this device. This setting is persisted across app sessions. By default it is enabled. */
	void SetAnalyticsCollectionEnabled(bool bEnabled) const;

	/** Get the instance ID from the analytics service. */
	void GetAnalyticsInstanceId(const FOnFirebaseAnalyticsGetAnalyticsInstanceIdCompleteDelegate& Delegate = FOnFirebaseAnalyticsGetAnalyticsInstanceIdCompleteDelegate()) const;

private:
	bool bInitialized = false;
};
