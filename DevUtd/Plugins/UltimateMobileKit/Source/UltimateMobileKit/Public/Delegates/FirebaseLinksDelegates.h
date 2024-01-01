// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "FirebaseLinksDelegates.generated.h"


/** The strength of a dynamic links match. */
UENUM(BlueprintType)
enum class EFirebaseLinksLinkMatchStrength : uint8
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

/** The desired path length for shortened Dynamic Link URLs. */
UENUM(BlueprintType)
enum class EFirebaseLinksPathLength : uint8
{
	/** Uses the server-default for the path length. See https://goo.gl/8yDAqC for more information. */
	Default,

	/** Typical short link for non-sensitive links. */
	Short,

	/** Short link that uses a very long path to make it more difficult to guess. Useful for sensitive links. */
	Unguessable
};

/** The received Dynamic Link. */
USTRUCT(BlueprintType)
struct FFirebaseDynamicLink
{
	GENERATED_USTRUCT_BODY()

	/** The match strength of the dynamic link. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	EFirebaseLinksLinkMatchStrength MatchStrength;

	/** The URL that was passed to the app. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString Url;

	FFirebaseDynamicLink()
	{
		MatchStrength = EFirebaseLinksLinkMatchStrength::NoMatch;
		Url = FString();
	}
};

/** Android Parameters. */
USTRUCT(BlueprintType)
struct FFirebaseAndroidParameters
{
	GENERATED_USTRUCT_BODY()

	/** The link to open when the app isn't installed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString FallbackUrl;

	/** The versionCode of the minimum version of your app that can open the link. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	int32 MinimumVersion;

	/** The package name of the Android app to use to open the link. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString PackageName;

	FFirebaseAndroidParameters()
	{
		FallbackUrl = FString();
		MinimumVersion = 0;
		PackageName = FString();
	}
};

/** iOS Parameters. */
USTRUCT(BlueprintType)
struct FFirebaseIOSParameters
{
	GENERATED_USTRUCT_BODY()

	/** The App Store ID, used to send users to the App Store when the app isn't installed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString AppStoreId;

	/** The parameters ID of the iOS app to use to open the link. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString BundleId;

	/** The app's custom URL scheme, if defined to be something other than your app's parameters ID. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString CustomScheme;

	/** The link to open on iOS if the app is not installed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString FallbackUrl;

	/** The iPad parameters ID of the app. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString IPadBundleId;

	/** The link to open on iPad if the app is not installed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString IPadFallbackUrl;

	/** The minimum version of your app that can open the link. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString MinimumVersion;

	FFirebaseIOSParameters()
	{
		AppStoreId = FString();
		BundleId = FString();
		CustomScheme = FString();
		FallbackUrl = FString();
		IPadBundleId = FString();
		IPadFallbackUrl = FString();
		MinimumVersion = FString();
	}
};

/** Google Analytics Parameters. */
USTRUCT(BlueprintType)
struct FFirebaseGoogleAnalyticsParameters
{
	GENERATED_USTRUCT_BODY()

	/** The campaign name; The individual campaign name, slogan, promo code, etc. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString Campaign;

	/** The campaign content; used for A/B testing and content-targeted ads to differentiate ads or links that point to the same URL. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString Content;

	/** The campaign medium; used to identify a medium such as email or cost-per-click (cpc). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString Medium;

	/** The campaign source; used to identify a search engine, newsletter, or other source. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString Source;

	/** The campaign term; used with paid search to supply the keywords for ads. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString Term;

	FFirebaseGoogleAnalyticsParameters()
	{
		Campaign = FString();
		Content = FString();
		Medium = FString();
		Source = FString();
		Term = FString();
	}
};

/** iTunes Connect App Analytics Parameters. */
USTRUCT(BlueprintType)
struct FFirebaseITunesConnectParameters
{
	GENERATED_USTRUCT_BODY()

	/** The affiliate token used to create affiliate-coded links. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString AffiliateToken;

	/** The campaign token that developers can add to any link in order to track sales from a specific marketing campaign. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString CampaignToken;

	/** The provider token that enables analytics for Dynamic Links from within iTunes Connect. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString ProviderToken;

	FFirebaseITunesConnectParameters()
	{
		AffiliateToken = FString();
		CampaignToken = FString();
		ProviderToken = FString();
	}
};

/** Social meta-tag Parameters. */
USTRUCT(BlueprintType)
struct FFirebaseSocialMetaTagParameters
{
	GENERATED_USTRUCT_BODY()

	/** The description to use when the Dynamic Link is shared in a social post. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString Description;

	/** The URL to an image related to this link. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString ImageUrl;

	/** The title to use when the Dynamic Link is shared in a social post. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString Title;

	FFirebaseSocialMetaTagParameters()
	{
		Description = FString();
		ImageUrl = FString();
		Title = FString();
	}
};

/** The returned value from creating a Dynamic Link. */
USTRUCT(BlueprintType)
struct FFirebaseGeneratedDynamicLink
{
	GENERATED_USTRUCT_BODY()

	/** If non-empty, the cause of the Dynamic Link generation failure. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString Error;

	/** The Dynamic Link value. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString Url;

	/** Information about potential warnings on link creation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	TArray<FString> Warnings;

	FFirebaseGeneratedDynamicLink()
	{
		Error = FString();
		Url = FString();
		Warnings = TArray<FString>();
	}
};

/** Additional options for Dynamic Link creation. */
USTRUCT(BlueprintType)
struct FFirebaseDynamicLinkOptions
{
	GENERATED_USTRUCT_BODY()

	/** The desired path length for shortened Dynamic Link URLs. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	EFirebaseLinksPathLength PathLength;

	FFirebaseDynamicLinkOptions()
	{
		PathLength = EFirebaseLinksPathLength::Default;
	}
};

/** The information needed to generate a Dynamic Link. */
USTRUCT(BlueprintType)
struct FFirebaseDynamicLinkComponents
{
	GENERATED_USTRUCT_BODY()

	/** The domain (of the form "xyz.app.goo.gl") to use for this Dynamic Link. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString DynamicLinkDomain;

	/** The link your app will open. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FString Link;

	/** The Android parameters. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FFirebaseAndroidParameters AndroidParameters;

	/** The Google Analytics parameters. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FFirebaseGoogleAnalyticsParameters GoogleAnalyticsParameters;

	/** The iOS parameters. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FFirebaseIOSParameters IOSParameters;

	/** The iTunes Connect App Analytics parameters. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FFirebaseITunesConnectParameters ITunesConnectAnalyticsParameters;

	/** The social meta-tag parameters. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Dynamic Links")
	FFirebaseSocialMetaTagParameters SocialMetaTagParameters;

	FFirebaseDynamicLinkComponents()
	{
		DynamicLinkDomain = FString();
		Link = FString();
		AndroidParameters = FFirebaseAndroidParameters();
		GoogleAnalyticsParameters = FFirebaseGoogleAnalyticsParameters();
		IOSParameters = FFirebaseIOSParameters();
		ITunesConnectAnalyticsParameters = FFirebaseITunesConnectParameters();
		SocialMetaTagParameters = FFirebaseSocialMetaTagParameters();
	}

	FFirebaseDynamicLinkComponents(const FString& InDynamicLinkDomain, const FString& InLink)
	{
		DynamicLinkDomain = InDynamicLinkDomain;
		Link = InLink;
		AndroidParameters = FFirebaseAndroidParameters();
		GoogleAnalyticsParameters = FFirebaseGoogleAnalyticsParameters();
		IOSParameters = FFirebaseIOSParameters();
		ITunesConnectAnalyticsParameters = FFirebaseITunesConnectParameters();
		SocialMetaTagParameters = FFirebaseSocialMetaTagParameters();
	}
};

/** Called when Firebase Dynamic Links module is initialized */
DECLARE_DELEGATE_OneParam(FOnFirebaseLinksInitializeCompleteDelegate, const bool);

/** Called when Firebase getting Short Dynamic Link is completed */
DECLARE_DELEGATE_TwoParams(FOnFirebaseLinksGetShortLinkCompleteDelegate, const bool, const FFirebaseGeneratedDynamicLink);
