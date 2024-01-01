// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Links/FirebaseLinks.h"
#include "Links/LinksInitialize.h"
#include "Links/LinksGetShortLink.h"

FFirebaseLinks::FFirebaseLinks()
{
}

FFirebaseLinks::~FFirebaseLinks()
{
}

void FFirebaseLinks::Init(UFirebaseLinksListener* Listener, const FOnFirebaseLinksInitializeCompleteDelegate& Delegate /*= FOnFirebaseLinksInitializeCompleteDelegate()*/)
{
	if (IsInitialized())
	{
		Delegate.ExecuteIfBound(true);
		return;
	}

	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		if(Listener != nullptr)
		{
			LinksListener = Listener;
			LinksListener->AddToRoot();
		}

		auto QueryTask = new FFirebaseLinksInitialize(UltimateMobileKit->Get(), Delegate, LinksListener);
		UltimateMobileKit->QueueAsyncTask(QueryTask);

		return;
	}

	Delegate.ExecuteIfBound(false);
}

void FFirebaseLinks::Shutdown()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Links Shutdown"));

	if(bInitialized)
	{
		if(LinksListener != nullptr)
		{
			LinksListener->RemoveFromRoot();
		}
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	firebase::dynamic_links::Terminate();
#endif
}

const bool FFirebaseLinks::IsInitialized() const
{
	return bInitialized;
}

void FFirebaseLinks::SetInitialized(bool Initialized)
{
	bInitialized = Initialized;

	if (bInitialized)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Links is initialized successfully"));
	}
	else
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Links is not initialized"));
	}
}

UFirebaseLinksListener* FFirebaseLinks::CreateListener() const
{
	if (IsInitialized() && LinksListener != nullptr)
	{
		return LinksListener;
	}
	else
	{
		return NewObject<UFirebaseLinksListener>();
	}
}

void FFirebaseLinks::Fetch() const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	if (IsInitialized())
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Links Fetch"));

		firebase::dynamic_links::Fetch();
	}
#endif
}

const FFirebaseGeneratedDynamicLink FFirebaseLinks::GetLongLink(const FFirebaseDynamicLinkComponents& DynamicLinkComponents) const
{
	FFirebaseGeneratedDynamicLink GeneratedDynamicLink;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	if (IsInitialized())
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Links Get Long Link"));

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

		firebase::dynamic_links::GeneratedDynamicLink GeneratedDynamicLinkTemp = firebase::dynamic_links::GetLongLink(*NativeDynamicLinkComponents);

		GeneratedDynamicLink.Error = FString(GeneratedDynamicLinkTemp.error.c_str());
		GeneratedDynamicLink.Url = FString(GeneratedDynamicLinkTemp.url.c_str());

		for (std::string warning : GeneratedDynamicLinkTemp.warnings)
		{
			GeneratedDynamicLink.Warnings.Add(FString(warning.c_str()));
		}
	}
#endif
	
	return GeneratedDynamicLink;
}

void FFirebaseLinks::GetShortLink(FFirebaseDynamicLinkComponents DynamicLinkComponents, const FOnFirebaseLinksGetShortLinkCompleteDelegate& Delegate /*= FOnFirebaseLinksGetShortLinkCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseLinksGetShortLink(UltimateMobileKit->Get(), Delegate, DynamicLinkComponents);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, FFirebaseGeneratedDynamicLink());
}

void FFirebaseLinks::GetShortLink(FFirebaseDynamicLinkComponents DynamicLinkComponents, FFirebaseDynamicLinkOptions DynamicLinkOptions, const FOnFirebaseLinksGetShortLinkCompleteDelegate& Delegate /*= FOnFirebaseLinksGetShortLinkCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseLinksGetShortLink(UltimateMobileKit->Get(), Delegate, DynamicLinkComponents, DynamicLinkOptions);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, FFirebaseGeneratedDynamicLink());
}

void FFirebaseLinks::GetShortLink(FString LongDynamicLink, const FOnFirebaseLinksGetShortLinkCompleteDelegate& Delegate /*= FOnFirebaseLinksGetShortLinkCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseLinksGetShortLink(UltimateMobileKit->Get(), Delegate, LongDynamicLink);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, FFirebaseGeneratedDynamicLink());
}

void FFirebaseLinks::GetShortLink(FString LongDynamicLink, FFirebaseDynamicLinkOptions DynamicLinkOptions, const FOnFirebaseLinksGetShortLinkCompleteDelegate& Delegate /*= FOnFirebaseLinksGetShortLinkCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseLinksGetShortLink(UltimateMobileKit->Get(), Delegate, LongDynamicLink, DynamicLinkOptions);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, FFirebaseGeneratedDynamicLink());
}
