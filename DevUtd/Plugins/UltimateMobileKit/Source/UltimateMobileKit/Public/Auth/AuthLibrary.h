// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthLibrary.generated.h"

/** Blueprint implementation of FirebaseAuth. Firebase Authentication provides backend services to securely authenticate users. It can authenticate users using passwords and federated identity provider credentials, and it can integrate with a custom auth backend. */
UCLASS()
class ULTIMATEMOBILEKIT_API UUltimateMobileKitAuth : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** Check if Firebase Authentication is initialized */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Authentication")
	static const bool IsFirebaseAuthenticationInitialized();

	/** Removes any existing authentication credentials from this client */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Sign Out")
	static void SignOut();

	/** Check if User is logged in */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Is User Logged In")
	static const bool IsUserLoggedIn();

	/** Synchronously gets the cached current user, or nullptr if there is none */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Get Logged User")
	static const FFirebaseUser GetLoggedUser();
};
