// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "InAppMessagingLibrary.generated.h"

/** Blueprint implementation of Firebase In-App Messaging. In-App Messaging engages active app users with contextual messages. */
UCLASS()
class ULTIMATEMOBILEKIT_API UUltimateMobileKitInAppMessaging : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** Check if Firebase In-App Messaging is initialized */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|In-App Messaging", DisplayName = "Is Firebase In-App Messaging Initialized")
	static const bool IsFirebaseInAppMessagingInitialized();

	/** Enable or disable automatic data collection for Firebase In-App Messaging. */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|In-App Messaging", DisplayName = "Firebase In-App Messaging Enable Automatic Data Collection")
	static void SetAutomaticDataCollectionEnabled(bool Enabled = true);

	/** Enable or disable suppression of Firebase In App Messaging messages. When enabled, no in app messages will be rendered until either you either disable suppression, or the app restarts, as this state is not preserved over app restarts. */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|In-App Messaging", DisplayName = "Firebase In-App Messaging Turn On Messages Suppressed")
	static void SetMessagesSuppressed(bool Suppresed = true);

	/** Determine whether automatic data collection is enabled or not */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|In-App Messaging", DisplayName = "Firebase In-App Messaging Is Automatic Data Collection Enabled")
	static bool IsAutomaticDataCollectionEnabled();

	/** Determine whether messages are suppressed or not. */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|In-App Messaging", DisplayName = "Firebase In-App Messaging Are Messages Suppressed")
	static bool AreMessagesSuppressed();
};
