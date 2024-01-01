// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Messaging/MessagingRequestPermissionProxy.h"
#include "UltimateMobileKit.h"

UFirebaseMessagingRequestPermissionProxy::UFirebaseMessagingRequestPermissionProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseMessagingRequestPermissionProxy* UFirebaseMessagingRequestPermissionProxy::RequestPermission()
{
	UFirebaseMessagingRequestPermissionProxy* Proxy = NewObject<UFirebaseMessagingRequestPermissionProxy>();
	return Proxy;
}

void UFirebaseMessagingRequestPermissionProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseMessagingPtr FirebaseMessaging = UltimateMobileKit->GetFirebaseMessaging();

		if (FirebaseMessaging.IsValid() && FirebaseMessaging->IsInitialized())
		{
			FOnFirebaseMessagingRequestPermissionCompleteDelegate RequestPermissionCompleteDelegate = FOnFirebaseMessagingRequestPermissionCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseMessaging->RequestPermission(RequestPermissionCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseMessagingError::Unknown);
}

void UFirebaseMessagingRequestPermissionProxy::OnQueryCompleted(const bool bSuccess, const EFirebaseMessagingError& Error)
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
