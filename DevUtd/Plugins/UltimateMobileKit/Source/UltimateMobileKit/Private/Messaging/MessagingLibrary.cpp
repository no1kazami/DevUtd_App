// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Messaging/MessagingLibrary.h"
#include "UltimateMobileKit.h"

UUltimateMobileKitMessaging::UUltimateMobileKitMessaging(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const bool UUltimateMobileKitMessaging::IsFirebaseMessagingInitialized()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseMessagingPtr FirebaseMessaging = UltimateMobileKit->GetFirebaseMessaging();

		if (FirebaseMessaging.IsValid())
		{
			return FirebaseMessaging->IsInitialized();
		}
	}

	return false;
}

void UUltimateMobileKitMessaging::Send(const FFirebaseMessage FirebaseMessage)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseMessagingPtr FirebaseMessaging = UltimateMobileKit->GetFirebaseMessaging();

		if (FirebaseMessaging.IsValid())
		{
			FirebaseMessaging->Send(FirebaseMessage);
		}
	}
}
