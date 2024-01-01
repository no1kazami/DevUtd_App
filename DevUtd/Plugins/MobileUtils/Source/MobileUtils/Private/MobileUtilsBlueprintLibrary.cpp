// Mobile Utils Plugin
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "MobileUtilsBlueprintLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"

UMobileUtilsBlueprintLibrary::UMobileUtilsBlueprintLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UMobileUtilsBlueprintLibrary::CheckInternetConnection()
{
#if PLATFORM_ANDROID || PLATFORM_IOS
	return IMobileUtils::Get().GetPlatformInterface()->CheckInternetConnection();
#else
	return true;
#endif
}

bool UMobileUtilsBlueprintLibrary::CheckGooglePlayServices()
{
#if PLATFORM_ANDROID || PLATFORM_IOS
	return IMobileUtils::Get().GetPlatformInterface()->CheckGooglePlayServices();
#else
	return false;
#endif
}

FString UMobileUtilsBlueprintLibrary::GetPersistentUniqueDeviceId()
{
#if PLATFORM_ANDROID || PLATFORM_IOS
	return IMobileUtils::Get().GetPlatformInterface()->GetPersistentUniqueDeviceId();
#else
	return UKismetSystemLibrary::GetUniqueDeviceId();
#endif
}

FString UMobileUtilsBlueprintLibrary::GetDeviceId()
{
#if PLATFORM_ANDROID || PLATFORM_IOS
	return IMobileUtils::Get().GetPlatformInterface()->GetDeviceId();
#else
	return UKismetSystemLibrary::GetUniqueDeviceId();
#endif
}

FString UMobileUtilsBlueprintLibrary::GetAuthToken()
{
	auto OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineIdentityPtr OnlineIdentity = OnlineSubsystem->GetIdentityInterface();
		if (OnlineIdentity.IsValid())
		{
			 return OnlineIdentity->GetAuthToken(0);
		}
	}

	return FString();
}

bool UMobileUtilsBlueprintLibrary::ToggleOrientation()
{
#if PLATFORM_ANDROID || PLATFORM_IOS 
	return IMobileUtils::Get().GetPlatformInterface()->ToggleOrientation();
#else 
	return false;
#endif 
}

bool UMobileUtilsBlueprintLibrary::SendEmail()
{
#if PLATFORM_ANDROID || PLATFORM_IOS 
	return IMobileUtils::Get().GetPlatformInterface()->SendEmail();
#else 
	return false;
#endif 
}

bool UMobileUtilsBlueprintLibrary::ShareApp()
{
#if PLATFORM_ANDROID || PLATFORM_IOS 
	return IMobileUtils::Get().GetPlatformInterface()->ShareApp();
#else 
	return false;
#endif 
}

bool UMobileUtilsBlueprintLibrary::NewSendEmail( FString emailAddress )
{
#if PLATFORM_ANDROID || PLATFORM_IOS 
	return IMobileUtils::Get().GetPlatformInterface()->NewSendEmail( emailAddress );
#else 
	return false;
#endif 
}

bool UMobileUtilsBlueprintLibrary::NewShareApp( FString shareAddres )
{
#if PLATFORM_ANDROID || PLATFORM_IOS 
	return IMobileUtils::Get().GetPlatformInterface()->NewShareApp( shareAddres );
#else 
	return false;
#endif 
}
