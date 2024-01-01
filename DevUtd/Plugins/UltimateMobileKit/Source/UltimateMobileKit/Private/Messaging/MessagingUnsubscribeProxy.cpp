// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Messaging/MessagingUnsubscribeProxy.h"
#include "UltimateMobileKit.h"

UFirebaseMessagingUnsubscribeProxy::UFirebaseMessagingUnsubscribeProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Topic("")
{
}

UFirebaseMessagingUnsubscribeProxy* UFirebaseMessagingUnsubscribeProxy::Unsubscribe(const FString& Topic)
{
	UFirebaseMessagingUnsubscribeProxy* Proxy = NewObject<UFirebaseMessagingUnsubscribeProxy>();
	Proxy->Topic = Topic;
	return Proxy;
}

void UFirebaseMessagingUnsubscribeProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseMessagingPtr FirebaseMessaging = UltimateMobileKit->GetFirebaseMessaging();

		if (FirebaseMessaging.IsValid() && FirebaseMessaging->IsInitialized())
		{
			FOnFirebaseMessagingUnsubscribeCompleteDelegate UnsubscribeCompleteDelegate = FOnFirebaseMessagingUnsubscribeCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseMessaging->Unsubscribe(Topic, UnsubscribeCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseMessagingError::Unknown);
}

void UFirebaseMessagingUnsubscribeProxy::OnQueryCompleted(const bool bSuccess, const EFirebaseMessagingError& Error)
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
