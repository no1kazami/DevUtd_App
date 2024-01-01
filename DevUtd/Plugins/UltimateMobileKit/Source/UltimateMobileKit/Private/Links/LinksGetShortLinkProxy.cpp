// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Links/LinksGetShortLinkProxy.h"
#include "UltimateMobileKit.h"

UFirebaseLinksGetShortLinkProxy::UFirebaseLinksGetShortLinkProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseLinksGetShortLinkProxy* UFirebaseLinksGetShortLinkProxy::GetShortLink(const FFirebaseDynamicLinkComponents DynamicLinkComponents, const FFirebaseDynamicLinkOptions DynamicLinkOptions, const FString& LongDynamicLink)
{
	UFirebaseLinksGetShortLinkProxy* Proxy = NewObject<UFirebaseLinksGetShortLinkProxy>();
	Proxy->DynamicLinkComponents = DynamicLinkComponents;
	Proxy->DynamicLinkOptions = DynamicLinkOptions;
	Proxy->LongDynamicLink = LongDynamicLink;
	return Proxy;
}

void UFirebaseLinksGetShortLinkProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseLinksPtr FirebaseLinks = UltimateMobileKit->GetFirebaseLinks();

		if (FirebaseLinks.IsValid())
		{
			FOnFirebaseLinksGetShortLinkCompleteDelegate GetShortLinkCompleteDelegate = FOnFirebaseLinksGetShortLinkCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			if(LongDynamicLink.Len() > 0)
			{
				FirebaseLinks->GetShortLink(LongDynamicLink, DynamicLinkOptions, GetShortLinkCompleteDelegate);
			}
			else
			{
				FirebaseLinks->GetShortLink(DynamicLinkComponents, DynamicLinkOptions, GetShortLinkCompleteDelegate);
			}

			return;
		}
	}

	OnFailure.Broadcast();
}

void UFirebaseLinksGetShortLinkProxy::OnQueryCompleted(bool bSuccess, const FFirebaseGeneratedDynamicLink GeneratedDynamicLink)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(GeneratedDynamicLink);
	}
	else
	{
		OnFailure.Broadcast();
	}
}
