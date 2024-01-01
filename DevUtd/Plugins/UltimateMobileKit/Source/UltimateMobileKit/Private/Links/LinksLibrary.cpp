// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Links/LinksLibrary.h"
#include "UltimateMobileKit.h"

UUltimateMobileKitLinks::UUltimateMobileKitLinks(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const bool UUltimateMobileKitLinks::IsFirebaseLinksInitialized()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseLinksPtr FirebaseLinks = UltimateMobileKit->GetFirebaseLinks();

		if (FirebaseLinks.IsValid())
		{
			return FirebaseLinks->IsInitialized();
		}
	}

	return false;
}

void UUltimateMobileKitLinks::Fetch()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseLinksPtr FirebaseLinks = UltimateMobileKit->GetFirebaseLinks();

		if (FirebaseLinks.IsValid())
		{
			FirebaseLinks->Fetch();
		}
	}
}

UFirebaseLinksListener* UUltimateMobileKitLinks::CreateListener()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseLinksPtr FirebaseLinks = UltimateMobileKit->GetFirebaseLinks();

		if (FirebaseLinks.IsValid())
		{
			return FirebaseLinks->CreateListener();
		}
	}

	return nullptr;
}

const FFirebaseGeneratedDynamicLink UUltimateMobileKitLinks::GetLongLink(const FFirebaseDynamicLinkComponents& DynamicLinkComponents)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseLinksPtr FirebaseLinks = UltimateMobileKit->GetFirebaseLinks();

		if (FirebaseLinks.IsValid())
		{
			return FirebaseLinks->GetLongLink(DynamicLinkComponents);
		}
	}

	return FFirebaseGeneratedDynamicLink();
}
