// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Messaging/MessagingInitializeProxy.h"
#include "UltimateMobileKit.h"

UFirebaseMessagingInitializeProxy::UFirebaseMessagingInitializeProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseMessagingInitializeProxy* UFirebaseMessagingInitializeProxy::Init(bool RequestPermission /*= true*/)
{
	UFirebaseMessagingInitializeProxy* Proxy = NewObject<UFirebaseMessagingInitializeProxy>();
	Proxy->RequestPermission = RequestPermission;
	return Proxy;
}

void UFirebaseMessagingInitializeProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseMessagingPtr FirebaseMessaging = UltimateMobileKit->GetFirebaseMessaging();

		if (FirebaseMessaging.IsValid())
		{
			FOnFirebaseMessagingInitializeCompleteDelegate InitializeCompleteDelegate = FOnFirebaseMessagingInitializeCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseMessaging->Init(RequestPermission, InitializeCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast();
}

void UFirebaseMessagingInitializeProxy::OnQueryCompleted(bool bSuccess)
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
