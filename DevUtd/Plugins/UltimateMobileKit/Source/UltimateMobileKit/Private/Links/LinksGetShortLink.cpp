// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Links/LinksGetShortLink.h"
#include "UltimateMobileKit.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
#include "firebase/dynamic_links.h"
#include "firebase/util.h"
#endif

FFirebaseLinksGetShortLink::FFirebaseLinksGetShortLink(FUltimateMobileKit* InSubsystem, const FOnFirebaseLinksGetShortLinkCompleteDelegate& InDelegate, const FFirebaseDynamicLinkComponents& InDynamicLinkComponents)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, DynamicLinkComponents(InDynamicLinkComponents)
{
	bUseDynamicLinkComponents = true;
}

FFirebaseLinksGetShortLink::FFirebaseLinksGetShortLink(FUltimateMobileKit* InSubsystem, const FOnFirebaseLinksGetShortLinkCompleteDelegate& InDelegate, const FFirebaseDynamicLinkComponents& InDynamicLinkComponents, const FFirebaseDynamicLinkOptions& InDynamicLinkOptions)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, DynamicLinkComponents(InDynamicLinkComponents)
	, DynamicLinkOptions(InDynamicLinkOptions)
{
	bUseDynamicLinkComponents = true;
	bUseDynamicLinkOptions = true;
}

FFirebaseLinksGetShortLink::FFirebaseLinksGetShortLink(FUltimateMobileKit* InSubsystem, const FOnFirebaseLinksGetShortLinkCompleteDelegate& InDelegate, const FString& InLongDynamicLink)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, LongDynamicLink(InLongDynamicLink)
{
	bUseLongDynamicLink = true;
}

FFirebaseLinksGetShortLink::FFirebaseLinksGetShortLink(FUltimateMobileKit* InSubsystem, const FOnFirebaseLinksGetShortLinkCompleteDelegate& InDelegate, const FString& InLongDynamicLink, const FFirebaseDynamicLinkOptions& InDynamicLinkOptions)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, DynamicLinkOptions(InDynamicLinkOptions)
	, LongDynamicLink(InLongDynamicLink)
{
	bUseLongDynamicLink = true;
	bUseDynamicLinkOptions = true;
}

void FFirebaseLinksGetShortLink::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseLinksGetShortLink async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseLinksPtr FirebaseLinks = UltimateMobileKit->GetFirebaseLinks();

		if(FirebaseLinks.IsValid() && FirebaseLinks->IsInitialized())
		{	
			// Dynamic Link Components
			TSharedPtr<firebase::dynamic_links::DynamicLinkComponents, ESPMode::ThreadSafe> NativeDynamicLinkComponents = MakeShareable(new firebase::dynamic_links::DynamicLinkComponents());

			// Android Parameters
			TSharedPtr<firebase::dynamic_links::AndroidParameters, ESPMode::ThreadSafe> NativeAndroidParameters = MakeShareable(new firebase::dynamic_links::AndroidParameters());

			TSharedPtr<std::string, ESPMode::ThreadSafe> AndroidFallbackUrlShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.AndroidParameters.FallbackUrl)));
			if (DynamicLinkComponents.AndroidParameters.FallbackUrl.Len() > 0)
			{
				NativeAndroidParameters->fallback_url = AndroidFallbackUrlShared->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> AndroidPackageNameShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.AndroidParameters.PackageName)));
			if (DynamicLinkComponents.AndroidParameters.PackageName.Len() > 0)
			{
				NativeAndroidParameters->package_name = AndroidPackageNameShared->c_str();
			}

			NativeAndroidParameters->minimum_version = DynamicLinkComponents.AndroidParameters.MinimumVersion;


			// Google Analytics Parameters
			TSharedPtr<firebase::dynamic_links::GoogleAnalyticsParameters, ESPMode::ThreadSafe> NativeGoogleAnalyticsParameters = MakeShareable(new firebase::dynamic_links::GoogleAnalyticsParameters());

			TSharedPtr<std::string, ESPMode::ThreadSafe> GoogleAnalyticsCampaignShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.GoogleAnalyticsParameters.Campaign)));
			if (DynamicLinkComponents.GoogleAnalyticsParameters.Campaign.Len() > 0)
			{
				NativeGoogleAnalyticsParameters->campaign = GoogleAnalyticsCampaignShared->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> GoogleAnalyticsContentShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.GoogleAnalyticsParameters.Content)));
			if (DynamicLinkComponents.GoogleAnalyticsParameters.Content.Len() > 0)
			{
				NativeGoogleAnalyticsParameters->content = GoogleAnalyticsContentShared->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> GoogleAnalyticsMediumShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.GoogleAnalyticsParameters.Medium)));
			if (DynamicLinkComponents.GoogleAnalyticsParameters.Medium.Len() > 0)
			{
				NativeGoogleAnalyticsParameters->medium = GoogleAnalyticsMediumShared->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> GoogleAnalyticsSourceShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.GoogleAnalyticsParameters.Source)));
			if (DynamicLinkComponents.GoogleAnalyticsParameters.Source.Len() > 0)
			{
				NativeGoogleAnalyticsParameters->source = GoogleAnalyticsSourceShared->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> GoogleAnalyticsTermShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.GoogleAnalyticsParameters.Term)));
			if (DynamicLinkComponents.GoogleAnalyticsParameters.Term.Len() > 0)
			{
				NativeGoogleAnalyticsParameters->term = GoogleAnalyticsTermShared->c_str();
			}


			// IOS Parameters
			TSharedPtr<firebase::dynamic_links::IOSParameters, ESPMode::ThreadSafe> NativeIOSParameters = MakeShareable(new firebase::dynamic_links::IOSParameters());
			
			TSharedPtr<std::string, ESPMode::ThreadSafe> IOSAppStoreIdShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.IOSParameters.AppStoreId)));
			if (DynamicLinkComponents.IOSParameters.AppStoreId.Len() > 0)
			{
				NativeIOSParameters->app_store_id = IOSAppStoreIdShared->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> IOSBundleIdShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.IOSParameters.BundleId)));
			if (DynamicLinkComponents.IOSParameters.BundleId.Len() > 0)
			{
				NativeIOSParameters->bundle_id = IOSBundleIdShared->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> IOSCustomSchemeShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.IOSParameters.CustomScheme)));
			if (DynamicLinkComponents.IOSParameters.CustomScheme.Len() > 0)
			{
				NativeIOSParameters->custom_scheme = IOSCustomSchemeShared->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> IOSFallbackUrlShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.IOSParameters.FallbackUrl)));
			if (DynamicLinkComponents.IOSParameters.FallbackUrl.Len() > 0)
			{
				NativeIOSParameters->fallback_url = IOSFallbackUrlShared->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> IOSIPadBundleIdShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.IOSParameters.IPadBundleId)));
			if (DynamicLinkComponents.IOSParameters.IPadBundleId.Len() > 0)
			{
				NativeIOSParameters->ipad_bundle_id = IOSIPadBundleIdShared->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> IOSIPadFallbackUrl = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.IOSParameters.IPadFallbackUrl)));
			if (DynamicLinkComponents.IOSParameters.IPadFallbackUrl.Len() > 0)
			{
				NativeIOSParameters->ipad_fallback_url = IOSIPadFallbackUrl->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> IOSMinimumVersionShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.IOSParameters.MinimumVersion)));
			if (DynamicLinkComponents.IOSParameters.MinimumVersion.Len() > 0)
			{
				NativeIOSParameters->minimum_version = IOSMinimumVersionShared->c_str();
			}


			// iTunes Analytics Parameters
			TSharedPtr<firebase::dynamic_links::ITunesConnectAnalyticsParameters, ESPMode::ThreadSafe> NativeITunesConnectAnalyticsParameters = MakeShareable(new firebase::dynamic_links::ITunesConnectAnalyticsParameters());

			TSharedPtr<std::string, ESPMode::ThreadSafe> ITunesAffiliateTokenShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.ITunesConnectAnalyticsParameters.AffiliateToken)));
			if (DynamicLinkComponents.ITunesConnectAnalyticsParameters.AffiliateToken.Len() > 0)
			{
				NativeITunesConnectAnalyticsParameters->affiliate_token = ITunesAffiliateTokenShared->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> ITunesCampaignTokenShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.ITunesConnectAnalyticsParameters.CampaignToken)));
			if (DynamicLinkComponents.ITunesConnectAnalyticsParameters.CampaignToken.Len() > 0)
			{
				NativeITunesConnectAnalyticsParameters->campaign_token = ITunesCampaignTokenShared->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> ITunesProviderTokenShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.ITunesConnectAnalyticsParameters.ProviderToken)));
			if (DynamicLinkComponents.ITunesConnectAnalyticsParameters.ProviderToken.Len() > 0)
			{
				NativeITunesConnectAnalyticsParameters->provider_token = ITunesProviderTokenShared->c_str();
			}


			// Social Meta Tag Parameters
			TSharedPtr<firebase::dynamic_links::SocialMetaTagParameters, ESPMode::ThreadSafe> NativeSocialMetaTagParameters = MakeShareable(new firebase::dynamic_links::SocialMetaTagParameters());

			TSharedPtr<std::string, ESPMode::ThreadSafe> SocialMetaTagDescriptionShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.SocialMetaTagParameters.Description)));
			if (DynamicLinkComponents.SocialMetaTagParameters.Description.Len() > 0)
			{
				NativeSocialMetaTagParameters->description = SocialMetaTagDescriptionShared->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> SocialMetaTagImageUrlShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.SocialMetaTagParameters.ImageUrl)));
			if (DynamicLinkComponents.SocialMetaTagParameters.ImageUrl.Len() > 0)
			{
				NativeSocialMetaTagParameters->image_url = SocialMetaTagImageUrlShared->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> SocialMetaTagTitleShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.SocialMetaTagParameters.Title)));
			if (DynamicLinkComponents.SocialMetaTagParameters.Title.Len() > 0)
			{
				NativeSocialMetaTagParameters->title = SocialMetaTagTitleShared->c_str();
			}


			// Dynamic Link Components
			TSharedPtr<std::string, ESPMode::ThreadSafe> DynamicLinkDomainShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.DynamicLinkDomain)));
			if (DynamicLinkComponents.DynamicLinkDomain.Len() > 0)
			{
				NativeDynamicLinkComponents->dynamic_link_domain = DynamicLinkDomainShared->c_str();
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> DynamicLinkLinkShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*DynamicLinkComponents.Link)));
			if (DynamicLinkComponents.Link.Len() > 0)
			{
				NativeDynamicLinkComponents->link = DynamicLinkLinkShared->c_str();
			}

			NativeDynamicLinkComponents->android_parameters = NativeAndroidParameters.Get();
			NativeDynamicLinkComponents->google_analytics_parameters = NativeGoogleAnalyticsParameters.Get();
			NativeDynamicLinkComponents->ios_parameters = NativeIOSParameters.Get();
			NativeDynamicLinkComponents->itunes_connect_analytics_parameters = NativeITunesConnectAnalyticsParameters.Get();
			NativeDynamicLinkComponents->social_meta_tag_parameters = NativeSocialMetaTagParameters.Get();

			// Dynamic Link Options
			TSharedPtr<firebase::dynamic_links::DynamicLinkOptions, ESPMode::ThreadSafe> NativeDynamicLinkOptions = MakeShareable(new firebase::dynamic_links::DynamicLinkOptions());

			if (DynamicLinkOptions.PathLength == EFirebaseLinksPathLength::Default)
			{
				NativeDynamicLinkOptions->path_length = firebase::dynamic_links::kPathLengthDefault;
			}
			else if (DynamicLinkOptions.PathLength == EFirebaseLinksPathLength::Short)
			{
				NativeDynamicLinkOptions->path_length = firebase::dynamic_links::kPathLengthShort;
			}
			else if (DynamicLinkOptions.PathLength == EFirebaseLinksPathLength::Unguessable)
			{
				NativeDynamicLinkOptions->path_length = firebase::dynamic_links::kPathLengthUnguessable;
			}

			if(bUseDynamicLinkComponents && bUseDynamicLinkOptions)
			{
				FetchFutureResult = firebase::dynamic_links::GetShortLink(*NativeDynamicLinkComponents, *NativeDynamicLinkOptions);
			}
			else if (bUseLongDynamicLink && bUseDynamicLinkOptions)
			{
				FetchFutureResult = firebase::dynamic_links::GetShortLink(TCHAR_TO_UTF8(*LongDynamicLink), *NativeDynamicLinkOptions);
			}
			else if (bUseDynamicLinkComponents)
			{
				FetchFutureResult = firebase::dynamic_links::GetShortLink(*NativeDynamicLinkComponents);
			}
			else if (bUseLongDynamicLink)
			{
				FetchFutureResult = firebase::dynamic_links::GetShortLink(TCHAR_TO_UTF8(*LongDynamicLink));
			}

			return;
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseLinksGetShortLink::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	if (FetchFutureResult.status() == firebase::kFutureStatusComplete)
	{
		if (FetchFutureResult.error() == 0)
		{
			bWasSuccessful = true;
			const firebase::dynamic_links::GeneratedDynamicLink* GeneratedDynamicLinkTemp = FetchFutureResult.result();

			if(GeneratedDynamicLinkTemp != nullptr)
			{
				GeneratedDynamicLink.Error = FString(GeneratedDynamicLinkTemp->error.c_str());
				GeneratedDynamicLink.Url = FString(GeneratedDynamicLinkTemp->url.c_str());

				for (std::string warning : GeneratedDynamicLinkTemp->warnings)
				{
					GeneratedDynamicLink.Warnings.Add(FString(warning.c_str()));
				}
			}
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseLinksGetShortLink Error: %s"), *FString(FetchFutureResult.error_message()));
		}
		bIsComplete = true;
	}

	if (FetchFutureResult.status() == firebase::kFutureStatusInvalid)
	{
		bWasSuccessful = false;
		bIsComplete = true;
	}
#endif
}

void FFirebaseLinksGetShortLink::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseLinksGetShortLink async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, GeneratedDynamicLink);
}

void FFirebaseLinksGetShortLink::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	FetchFutureResult.Release();
#endif
}
