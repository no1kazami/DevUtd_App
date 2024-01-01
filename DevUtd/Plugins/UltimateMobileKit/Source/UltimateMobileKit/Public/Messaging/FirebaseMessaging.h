// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "Delegates/FirebaseMessagingDelegates.h"


#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
#include "firebase/messaging.h"
#endif

/** Firebase Messaging allows to send data from server to users' devices, and receive messages from devices on the same connection if user is using a XMPP server. The FCM service handles all aspects of queueing of messages and delivery to client applications running on target devices. */
class ULTIMATEMOBILEKIT_API FFirebaseMessaging
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	: public firebase::messaging::Listener
#endif
{
public:
	FFirebaseMessaging();
	virtual ~FFirebaseMessaging();

	/** Initialize the Firebase Messaging API  */
	void Init(bool RequestPermission = true, const FOnFirebaseMessagingInitializeCompleteDelegate& Delegate = FOnFirebaseMessagingInitializeCompleteDelegate());

	/** Shutdown the Firebase Messaging API  */
	void Shutdown();

	/** Check if Firebase Messaging is initialized */
	const bool IsInitialized() const;

	/** Set Firebase Messaging initialization state */
	void SetInitialized(bool Initialized);

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	/** Called on the client when a message arrives */
	virtual void OnMessage(const firebase::messaging::Message& message);

	/** Called on the client when a registration token arrives */
	virtual void OnTokenReceived(const char* token);
#endif

	/** Subscribe to receive all messages to the specified topic */
	void Subscribe(const FString& Topic, const FOnFirebaseMessagingSubscribeCompleteDelegate& Delegate = FOnFirebaseMessagingSubscribeCompleteDelegate()) const;

	/** Unsubscribe from a topic */
	void Unsubscribe(const FString& Topic, const FOnFirebaseMessagingUnsubscribeCompleteDelegate& Delegate = FOnFirebaseMessagingUnsubscribeCompleteDelegate()) const;

	/** Displays a prompt to the user requesting permission to display notifications. */
	void RequestPermission(const FOnFirebaseMessagingRequestPermissionCompleteDelegate& Delegate = FOnFirebaseMessagingRequestPermissionCompleteDelegate()) const;

	/** Send an upstream ("device to cloud") message */
	void Send(const FFirebaseMessage FirebaseMessage) const;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	/** Transform Native Message To Unreal Message */
	const FFirebaseMessage TransformNativeToUnrealMessage(const firebase::messaging::Message& NativeMessage) const;
    
    /** Transform Unreal To Native Message */
	TSharedRef<firebase::messaging::Message, ESPMode::ThreadSafe> TransformUnrealToNativeMessage(const FFirebaseMessage FirebaseMessage) const;

	/** Convert Native Firebase Messaging Error to Unreal Firebase Error */
	static const EFirebaseMessagingError FirebaseErrorFromNative(const firebase::messaging::Error& NativeError);
#endif

private:
	bool bInitialized = false;
};
