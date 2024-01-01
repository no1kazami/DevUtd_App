// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "InAppMessaging/InAppMessagingLibrary.h"
#include "UltimateMobileKit.h"

UUltimateMobileKitInAppMessaging::UUltimateMobileKitInAppMessaging(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const bool UUltimateMobileKitInAppMessaging::IsFirebaseInAppMessagingInitialized()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInAppMessagingPtr FirebaseInAppMessaging = UltimateMobileKit->GetFirebaseInAppMessaging();

		if (FirebaseInAppMessaging.IsValid())
		{
			return FirebaseInAppMessaging->IsInitialized();
		}
	}

	return false;
}

void UUltimateMobileKitInAppMessaging::SetAutomaticDataCollectionEnabled(bool Enabled /*= true*/)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInAppMessagingPtr FirebaseInAppMessaging = UltimateMobileKit->GetFirebaseInAppMessaging();

		if (FirebaseInAppMessaging.IsValid())
		{
			FirebaseInAppMessaging->SetAutomaticDataCollectionEnabled(Enabled);
		}
	}
}

void UUltimateMobileKitInAppMessaging::SetMessagesSuppressed(bool Suppresed /*= true*/)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInAppMessagingPtr FirebaseInAppMessaging = UltimateMobileKit->GetFirebaseInAppMessaging();

		if (FirebaseInAppMessaging.IsValid())
		{
			FirebaseInAppMessaging->SetMessagesSuppressed(Suppresed);
		}
	}
}

bool UUltimateMobileKitInAppMessaging::IsAutomaticDataCollectionEnabled()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInAppMessagingPtr FirebaseInAppMessaging = UltimateMobileKit->GetFirebaseInAppMessaging();

		if (FirebaseInAppMessaging.IsValid())
		{
			return FirebaseInAppMessaging->IsAutomaticDataCollectionEnabled();
		}
	}

	return false;
}

bool UUltimateMobileKitInAppMessaging::AreMessagesSuppressed()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInAppMessagingPtr FirebaseInAppMessaging = UltimateMobileKit->GetFirebaseInAppMessaging();

		if (FirebaseInAppMessaging.IsValid())
		{
			return FirebaseInAppMessaging->AreMessagesSuppressed();
		}
	}

	return false;
}
