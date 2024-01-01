// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Delegates/FirebaseMessagingDelegates.h"
#include "MessagingLibrary.generated.h"

/** Blueprint implementation of FirebaseMessaging. Firebase Messaging allows to send data from server to users' devices, and receive messages from devices on the same connection if user is using a XMPP server. The FCM service handles all aspects of queueing of messages and delivery to client applications running on target devices. */
UCLASS()
class ULTIMATEMOBILEKIT_API UUltimateMobileKitMessaging : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** Check if Firebase Messaging is initialized */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Messaging")
	static const bool IsFirebaseMessagingInitialized();

	/** Send an upstream ("device to cloud") message */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Messaging", DisplayName = "Firebase Messaging Send Message")
	static void Send(const FFirebaseMessage FirebaseMessage);
};
