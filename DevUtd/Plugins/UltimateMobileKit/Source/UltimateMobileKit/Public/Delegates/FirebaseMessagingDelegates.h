// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "FirebaseMessagingDelegates.generated.h"

/** Error code returned by Firebase Messaging functions. */
UENUM(BlueprintType)
enum class EFirebaseMessagingError : uint8
{
	/** None */
	None,

	/** Failed To Register For Remote Notifications */
	FailedToRegisterForRemoteNotifications,

	/** Invalid Topic Name */
	InvalidTopicName,

	/** Unknown */
	Unknown
};

/** Called when Firebase Messaging module is initialized */
DECLARE_DELEGATE_OneParam(FOnFirebaseMessagingInitializeCompleteDelegate, const bool);

/** Called when Firebase Messaging Subscribe completed successfully */
DECLARE_DELEGATE_TwoParams(FOnFirebaseMessagingSubscribeCompleteDelegate, const bool, const EFirebaseMessagingError&);

/** Called when Firebase Messaging Unsubscribe completed successfully */
DECLARE_DELEGATE_TwoParams(FOnFirebaseMessagingUnsubscribeCompleteDelegate, const bool, const EFirebaseMessagingError&);

/** Called when Firebase Messaging Request Permission completed successfully */
DECLARE_DELEGATE_TwoParams(FOnFirebaseMessagingRequestPermissionCompleteDelegate, const bool, const EFirebaseMessagingError&);

/** Used for messages that display a notification */
USTRUCT(BlueprintType)
struct FFirebaseNotification
{
	GENERATED_USTRUCT_BODY()

	/** Indicates the badge on the client app home icon. iOS only */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString Badge;

	/** Indicates notification body text */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString Body;

	/** Indicates the string value to replace format specifiers in body string for localization */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	TArray<FString> BodyLocArgs;

	/** Indicates the key to the body string for localization */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString BodyLocKey;

	/** The action associated with a user click on the notification */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString ClickAction;

	/** Indicates color of the icon, expressed in #rrggbb format. Android only */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString Color;

	/** Indicates notification icon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString Icon;

	/** Indicates a sound to play when the device receives the notification */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString Sound;

	/** Indicates whether each notification results in a new entry in the notification drawer on Android */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString Tag;

	/** Indicates notification title */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString Title;

	/** Indicates the string value to replace format specifiers in title string for localization */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	TArray<FString> TitleLocArgs;

	/** Indicates the key to the title string for localization */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString TitleLocKey;

	FFirebaseNotification()
	{
		Badge = FString();
		Body = FString();
		BodyLocArgs = TArray<FString>();
		BodyLocKey = FString();
		ClickAction = FString();
		Color = FString();
		Icon = FString();
		Sound = FString();
		Tag = FString();
		Title = FString();
		TitleLocArgs = TArray<FString>();
		TitleLocKey = FString();
	}
};

/** Data structure used to send messages to, and receive messages from, cloud messaging */
USTRUCT(BlueprintType)
struct FFirebaseMessage
{
	GENERATED_USTRUCT_BODY()

	/** The collapse key used for collapsible messages */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString CollapseKey;

	/** The metadata, including all original key/value pairs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	TMap<FString, FString> Data;

	/** Error code */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString Error;

	/** Human readable details about the error */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString ErrorDescription;

	/** Authenticated ID of the sender */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString From;

	/** The link into the app from the message */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString Link;

	/** Message ID */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString MessageId;

	/** Equivalent with a content-type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString MessageType;

	/** Optional notification to show */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FFirebaseNotification Notification;

	/** A flag indicating whether this message was opened by tapping a notification in the OS system tray */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	bool NotificationOpened;

	/** Priority level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString Priority;

	/** Binary payload */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString RawData;

	/** Time to live, in seconds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	int32 TimeToLive;

	/** This parameter specifies the recipient of a message */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Messaging")
	FString To;

	FFirebaseMessage()
	{
		CollapseKey = FString();
		Data = TMap<FString, FString>();
		Error = FString();
		ErrorDescription = FString();
		From = FString();
		MessageId = FString();
		MessageType = FString();
		NotificationOpened = false;
		Priority = FString();
		RawData = FString();
		TimeToLive = 0;
		To = FString();
	}
};
