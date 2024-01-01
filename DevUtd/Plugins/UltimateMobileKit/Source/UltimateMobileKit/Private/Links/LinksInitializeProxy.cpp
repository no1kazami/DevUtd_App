// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Links/LinksInitializeProxy.h"
#include "UltimateMobileKit.h"

UFirebaseLinksInitializeProxy::UFirebaseLinksInitializeProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseLinksInitializeProxy* UFirebaseLinksInitializeProxy::Init(UFirebaseLinksListener* Listener)
{
	UFirebaseLinksInitializeProxy* Proxy = NewObject<UFirebaseLinksInitializeProxy>();
	Proxy->LinksListener = Listener;
	return Proxy;
}

void UFirebaseLinksInitializeProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseLinksPtr FirebaseLinks = UltimateMobileKit->GetFirebaseLinks();

		if (FirebaseLinks.IsValid())
		{
			FOnFirebaseLinksInitializeCompleteDelegate InitializeCompleteDelegate = FOnFirebaseLinksInitializeCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseLinks->Init(LinksListener, InitializeCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast();
}

void UFirebaseLinksInitializeProxy::OnQueryCompleted(bool bSuccess)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast();
	}
	else
	{
		OnFailure.Broadcast();
	}
}
