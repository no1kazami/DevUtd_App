// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Messaging/MessagingSubscribeProxy.h"
#include "UltimateMobileKit.h"

UFirebaseMessagingSubscribeProxy::UFirebaseMessagingSubscribeProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Topic("")
{
}

UFirebaseMessagingSubscribeProxy* UFirebaseMessagingSubscribeProxy::Subscribe(const FString& Topic)
{
	UFirebaseMessagingSubscribeProxy* Proxy = NewObject<UFirebaseMessagingSubscribeProxy>();
	Proxy->Topic = Topic;
	return Proxy;
}

void UFirebaseMessagingSubscribeProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseMessagingPtr FirebaseMessaging = UltimateMobileKit->GetFirebaseMessaging();

		if (FirebaseMessaging.IsValid() && FirebaseMessaging->IsInitialized())
		{
			FOnFirebaseMessagingSubscribeCompleteDelegate SubscribeCompleteDelegate = FOnFirebaseMessagingSubscribeCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseMessaging->Subscribe(Topic, SubscribeCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseMessagingError::Unknown);
}

void UFirebaseMessagingSubscribeProxy::OnQueryCompleted(const bool bSuccess, const EFirebaseMessagingError& Error)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(Error);
	}
	else
	{
		OnFailure.Broadcast(Error);
	}
}
