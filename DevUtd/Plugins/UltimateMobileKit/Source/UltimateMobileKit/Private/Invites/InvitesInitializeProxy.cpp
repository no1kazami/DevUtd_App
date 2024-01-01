// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Invites/InvitesInitializeProxy.h"
#include "UltimateMobileKit.h"

UFirebaseInvitesInitializeProxy::UFirebaseInvitesInitializeProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseInvitesInitializeProxy* UFirebaseInvitesInitializeProxy::Init()
{
	UFirebaseInvitesInitializeProxy* Proxy = NewObject<UFirebaseInvitesInitializeProxy>();
	return Proxy;
}

void UFirebaseInvitesInitializeProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInvitesPtr FirebaseInvites = UltimateMobileKit->GetFirebaseInvites();

		if (FirebaseInvites.IsValid())
		{
			FOnFirebaseInvitesInitializeCompleteDelegate InitializeCompleteDelegate = FOnFirebaseInvitesInitializeCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseInvites->Init(InitializeCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast();
}

void UFirebaseInvitesInitializeProxy::OnQueryCompleted(bool bSuccess)
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
