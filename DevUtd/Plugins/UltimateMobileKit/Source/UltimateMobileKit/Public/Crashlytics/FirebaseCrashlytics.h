// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

/** Firebase Crashlytics lets diagnose problems in game with detailed reports of bugs and crashes. */
class ULTIMATEMOBILEKIT_API FFirebaseCrashlytics
{
public:
	FFirebaseCrashlytics();
	virtual ~FFirebaseCrashlytics();

	/** Initialize the Firebase Crashlytics API  */
	void Init();

	/** Shutdown the Firebase Crashlytics API  */
	void Shutdown();

	/** Check if Firebase Crashlytics is initialized */
	const bool IsInitialized() const;

	/** The easiest way to cause a crash - great for testing! */
	void ForceCrash() const;

	/** The easiest way to cause an exception - great for testing! */
	void ForceException() const;

	/** Personalize by user identifier */
	void SetUserIdentifier(const FString& Identifier) const;

	/** Personalize by user email */
	void SetUserEmail(const FString& Email) const;

	/** Personalize by user name */
	void SetUsername(const FString& Username) const;

	/** Write custom log (dev and shipping build) */
	void WriteLog(const FString& Log) const;

	/** Write custom log with tag and priority (dev and shipping build) */
	void WriteLogWithTagAndPriority(const FString& Log, const FString& Tag, const int32 Priority) const;

	/** Add custom key with string value */
	void SetString(const FString& Key, const FString& Value) const;

	/** Add custom key with bool value */
	void SetBool(const FString& Key, const bool Value) const;

	/** Add custom key with float value */
	void SetFloat(const FString& Key, const float Value) const;

	/** Add custom key with integer value */
	void SetInteger(const FString& Key, const int32 Value) const;

private:
	bool bInitialized = false;
};
