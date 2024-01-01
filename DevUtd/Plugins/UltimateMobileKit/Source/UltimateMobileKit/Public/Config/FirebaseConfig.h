// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Delegates/FirebaseConfigDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
#include "firebase/remote_config.h"
#endif

/** Firebase Config lets change the appearance and behavior of game without requiring players to download an app update. */
class ULTIMATEMOBILEKIT_API FFirebaseConfig
{
public:
	FFirebaseConfig();
	virtual ~FFirebaseConfig();

	/** Initialize the Firebase Config API  */
	void Init(const TArray<UFirebaseVariant*> DefaultParameters, const FString& ConfigNamespace = FString(), const FOnFirebaseConfigInitializeCompleteDelegate& Delegate = FOnFirebaseConfigInitializeCompleteDelegate());

	/** Shutdown the Firebase Config API  */
	void Shutdown();

	/** Check if Firebase Config is initialized */
	const bool IsInitialized() const;

	/** Set Firebase Config initialization state */
	void SetInitialized(bool Initialized);

	/** Fetches config data from the server */
	void Fetch(const FOnFirebaseConfigFetchCompleteDelegate& Delegate = FOnFirebaseConfigFetchCompleteDelegate(), const int32 CacheExpirationInSeconds = 0) const;

	/** Applies the most recently fetched data, so that its values can be accessed */
	const bool ActivateFetched() const;

	/** Gets the set of all keys in the given namespace */
	const TArray<FString> GetKeys(const FString& ConfigNamespace = FString()) const;

	/** Gets the set of keys that start with the given prefix, in the given namespace */
	const TArray<FString> GetKeysByPrefix(const FString& Prefix, const FString& ConfigNamespace = FString()) const;

	/** Returns information about the last fetch request */
	const FRemoteConfigInfo GetInfo() const;

	/** Returns the value associated with a key, converted to a bool */
	const bool GetBoolean(const FString& Name, const FString& ConfigNamespace = FString()) const;

	/** Returns the value associated with a key, converted to a float */
	const float GetFloat(const FString& Name, const FString& ConfigNamespace = FString()) const;

	/** Returns the value associated with a key, converted to an integer */
	const int32 GetInteger(const FString& Name, const FString& ConfigNamespace = FString()) const;

	/** Returns the value associated with a key, converted to a string */
	const FString GetString(const FString& Name, const FString& ConfigNamespace = FString()) const;

private:
	bool bInitialized = false;
};
