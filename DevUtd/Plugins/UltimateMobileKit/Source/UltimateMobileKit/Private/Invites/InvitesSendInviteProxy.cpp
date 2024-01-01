// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Invites/InvitesSendInviteProxy.h"
#include "UltimateMobileKit.h"

UFirebaseInvitesSendInviteProxy::UFirebaseInvitesSendInviteProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseInvitesSendInviteProxy* UFirebaseInvitesSendInviteProxy::SendInvite(const FFirebaseInvite Invite)
{
	UFirebaseInvitesSendInviteProxy* Proxy = NewObject<UFirebaseInvitesSendInviteProxy>();
	Proxy->Invite = Invite;
	return Proxy;
}

void UFirebaseInvitesSendInviteProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInvitesPtr FirebaseInvites = UltimateMobileKit->GetFirebaseInvites();

		if (FirebaseInvites.IsValid())
		{
			FOnFirebaseInvitesSendInviteCompleteDelegate SendInviteCompleteDelegate = FOnFirebaseInvitesSendInviteCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseInvites->SendInvite(Invite, SendInviteCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast();
}

void UFirebaseInvitesSendInviteProxy::OnQueryCompleted(bool bSuccess, const FFirebaseSendInviteResult InviteResult)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(InviteResult);
	}
	else
	{
		OnFailure.Broadcast();
	}
}
