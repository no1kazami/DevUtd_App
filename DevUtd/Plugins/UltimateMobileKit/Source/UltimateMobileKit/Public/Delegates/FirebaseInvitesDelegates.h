// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "FirebaseInvitesDelegates.generated.h"


/** The strength of a dynamic links match. */
UENUM(BlueprintType)
enum class EFirebaseInvitesLinkMatchStrength : uint8
{
	/** No match has been achieved. */
	NoMatch,

	/** The match between the Dynamic Link and the device is exact. You may safely reveal any personal information related to this Dynamic Link. */
	WeakMatch,

	/** The match between the Dynamic Link and this device has a high confidence, but there is a small possibility of error. */
	StrongMatch,

	/** The match between the Dynamic Link and device is not perfect. You should not reveal any personal information related to the Dynamic Link. */
	PerfectMatch
};

/** Data structure used to construct and send an invite. */
USTRUCT(BlueprintType)
struct FFirebaseInvite
{
	GENERATED_USTRUCT_BODY()

	/** The title text for the Invites UI window */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Invites")
	FString TitleText;

	/** The text of the invitation message (Max 100 characters) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Invites")
	FString MessageText;

	/** The app description text for email invitations (Max 1000 characters) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Invites")
	FString DescriptionText;

	/** Text shown on the email invitation button for the user to accept the invitation (Max 20 characters) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Invites")
	FString CallToActionText;

	/** The URL for an image to include in the invitation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Invites")
	FString CustomImageUrl;

	/** The full HTML content of the invitation that will be sent (Max 512000 characters) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Invites")
	FString EmailContentHtml;

	/** The subject text for an HTML e-mail */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Invites")
	FString EmailSubjectText;

	/** An optional dynamic link that will be sent with the invitation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Invites")
	FString DeepLinkUrl;

	/** Optional minimum version of the android app installed on the receiving device */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Invites")
	int32 AndroidMinimumVersionCode;

	/** The client ID for your app for the Android platform (don't set this for your current platform) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Invites")
	FString AndroidPlatformClientId;

	/** The optional Google Analytics Tracking id */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Invites")
	FString GoogleAnalyticsTrackingId;

	/** The client ID for your app for the iOS platform (don't set this for your current platform) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Invites")
	FString IOSPlatformClientId;

	/** Optional additional referral parameters, which is passed to the invite URL as a key/value pair */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Invites")
	TMap<FString, FString> ReferralParameters;

	FFirebaseInvite()
	{
		TitleText = FString();
		MessageText = FString();
		DescriptionText = FString();
		CallToActionText = FString();
		CustomImageUrl = FString();
		EmailContentHtml = FString();
		EmailSubjectText = FString();
		DeepLinkUrl = FString();
		AndroidMinimumVersionCode = 0;
		AndroidPlatformClientId = FString();
		GoogleAnalyticsTrackingId = FString();
		IOSPlatformClientId = FString();
		ReferralParameters = TMap<FString, FString>();
	}
};

/** Results from calling SendInvite() to send an invitation. */
USTRUCT(BlueprintType)
struct FFirebaseSendInviteResult
{
	GENERATED_USTRUCT_BODY()

	/** The Invitation IDs we sent invites to, if any. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Invites")
	TArray<FString> InvitationIds;

	FFirebaseSendInviteResult()
	{
		InvitationIds = TArray<FString>();
	}
};

/** Called when Firebase Invites module is initialized */
DECLARE_DELEGATE_OneParam(FOnFirebaseInvitesInitializeCompleteDelegate, const bool);

/** Called when Firebase sending invitation is completed */
DECLARE_DELEGATE_TwoParams(FOnFirebaseInvitesSendInviteCompleteDelegate, const bool, const FFirebaseSendInviteResult);

/** Called when Firebase converting invitation is completed */
DECLARE_DELEGATE_OneParam(FOnFirebaseInvitesConvertInvitationCompleteDelegate, const bool);
