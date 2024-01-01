// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "Delegates/FirebaseInAppMessagingDelegates.h"

/** In-App Messaging engages active app users with contextual messages. */
class ULTIMATEMOBILEKIT_API FFirebaseInAppMessaging
{
public:
	FFirebaseInAppMessaging();
	virtual ~FFirebaseInAppMessaging();

	/** Initialize the Firebase In-App Messaging API  */
	void Init(const FOnFirebaseInAppMessagingInitializeCompleteDelegate& Delegate = FOnFirebaseInAppMessagingInitializeCompleteDelegate());

	/** Shutdown the Firebase In-App Messaging API  */
	void Shutdown();

	/** Check if Firebase In-App Messaging is initialized */
	const bool IsInitialized() const;

	/** Set Firebase In-App Messaging initialization state */
	void SetInitialized(const bool Initialized);

	/** Enable or disable automatic data collection for Firebase In-App Messaging. */
	void SetAutomaticDataCollectionEnabled(bool Enabled = true);

	/** Enable or disable suppression of Firebase In App Messaging messages. When enabled, no in app messages will be rendered until either you either disable suppression, or the app restarts, as this state is not preserved over app restarts. */
	void SetMessagesSuppressed(bool Suppresed = true);

	/** Determine whether automatic data collection is enabled or not */
	bool IsAutomaticDataCollectionEnabled();

	/** Determine whether messages are suppressed or not. */
	bool AreMessagesSuppressed();

private:
	bool bInitialized = false;
};
