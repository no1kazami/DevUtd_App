// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "InAppMessaging/InAppMessagingInitializeProxy.h"
#include "UltimateMobileKit.h"

UFirebaseInAppMessagingInitializeProxy::UFirebaseInAppMessagingInitializeProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseInAppMessagingInitializeProxy* UFirebaseInAppMessagingInitializeProxy::Init()
{
	UFirebaseInAppMessagingInitializeProxy* Proxy = NewObject<UFirebaseInAppMessagingInitializeProxy>();
	return Proxy;
}

void UFirebaseInAppMessagingInitializeProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInAppMessagingPtr FirebaseInAppMessaging = UltimateMobileKit->GetFirebaseInAppMessaging();

		if (FirebaseInAppMessaging.IsValid())
		{
			FOnFirebaseInAppMessagingInitializeCompleteDelegate InitializeCompleteDelegate = FOnFirebaseInAppMessagingInitializeCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseInAppMessaging->Init(InitializeCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast();
}

void UFirebaseInAppMessagingInitializeProxy::OnQueryCompleted(bool bSuccess)
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
