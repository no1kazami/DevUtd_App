// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Delegates/FirebaseConfigDelegates.h"
#include "ConfigLibrary.generated.h"

/** Blueprint implementation of FirebaseConfig. Firebase Config lets change the appearance and behavior of game without requiring players to download an app update. */
UCLASS()
class ULTIMATEMOBILEKIT_API UUltimateMobileKitConfig : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** Check if Firebase Config is initialized */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Remote Config", DisplayName = "Is Firebase Remote Config Initialized")
	static bool IsFirebaseConfigInitialized();

	/** Applies the most recently fetched data, so that its values can be accessed */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Remote Config", DisplayName = "Firebase Remote Config Activate Fetched")
	static bool ActivateFetched();

	/** Gets the set of all keys in the given namespace */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Remote Config", DisplayName = "Firebase Remote Config Get Keys")
	static TArray<FString> GetKeys(const FString& ConfigNamespace);

	/** Gets the set of keys that start with the given prefix, in the given namespace */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Remote Config", DisplayName = "Firebase Remote Config Get Keys By Prefix")
	static TArray<FString> GetKeysByPrefix(const FString& Prefix, const FString& ConfigNamespace);

	/** Returns information about the last fetch request */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Remote Config", DisplayName = "Firebase Remote Config Last Fetch Get Info")
	static const FRemoteConfigInfo GetInfo();

	/** Returns the value associated with a key, converted to a bool */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Remote Config", DisplayName = "Firebase Remote Config Get Boolean")
	static bool GetBoolean(const FString& Name, const FString& ConfigNamespace);

	/** Returns the value associated with a key, converted to a float */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Remote Config", DisplayName = "Firebase Remote Config Get Float")
	static float GetFloat(const FString& Name, const FString& ConfigNamespace);

	/** Returns the value associated with a key, converted to an integer */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Remote Config", DisplayName = "Firebase Remote Config Get Integer")
	static const int32 GetInteger(const FString& Name, const FString& ConfigNamespace);

	/** Returns the value associated with a key, converted to a string */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Remote Config", DisplayName = "Firebase Remote Config Get String")
	static const FString GetString(const FString& Name, const FString& ConfigNamespace);
};
