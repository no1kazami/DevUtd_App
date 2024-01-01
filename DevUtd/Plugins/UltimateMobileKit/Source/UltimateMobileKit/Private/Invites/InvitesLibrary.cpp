// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Invites/InvitesLibrary.h"
#include "UltimateMobileKit.h"

UUltimateMobileKitInvites::UUltimateMobileKitInvites(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const bool UUltimateMobileKitInvites::IsFirebaseInvitesInitialized()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInvitesPtr FirebaseInvites = UltimateMobileKit->GetFirebaseInvites();

		if (FirebaseInvites.IsValid())
		{
			return FirebaseInvites->IsInitialized();
		}
	}

	return false;
}

void UUltimateMobileKitInvites::Fetch()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInvitesPtr FirebaseInvites = UltimateMobileKit->GetFirebaseInvites();

		if (FirebaseInvites.IsValid())
		{
			FirebaseInvites->Fetch();
		}
	}
}

UFirebaseInvitesListener* UUltimateMobileKitInvites::GetListener()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInvitesPtr FirebaseInvites = UltimateMobileKit->GetFirebaseInvites();

		if (FirebaseInvites.IsValid())
		{
			return FirebaseInvites->GetListener();
		}
	}

	return nullptr;
}
