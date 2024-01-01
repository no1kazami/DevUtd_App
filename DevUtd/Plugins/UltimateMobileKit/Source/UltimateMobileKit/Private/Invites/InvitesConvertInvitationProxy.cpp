// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Invites/InvitesConvertInvitationProxy.h"
#include "UltimateMobileKit.h"

UFirebaseInvitesConvertInvitationProxy::UFirebaseInvitesConvertInvitationProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseInvitesConvertInvitationProxy* UFirebaseInvitesConvertInvitationProxy::ConvertInvitation(const FString& InvitationId)
{
	UFirebaseInvitesConvertInvitationProxy* Proxy = NewObject<UFirebaseInvitesConvertInvitationProxy>();
	Proxy->InvitationId = InvitationId;
	return Proxy;
}

void UFirebaseInvitesConvertInvitationProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInvitesPtr FirebaseInvites = UltimateMobileKit->GetFirebaseInvites();

		if (FirebaseInvites.IsValid())
		{
			FOnFirebaseInvitesConvertInvitationCompleteDelegate ConvertInvitationCompleteDelegate = FOnFirebaseInvitesConvertInvitationCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseInvites->ConvertInvitation(InvitationId, ConvertInvitationCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast();
}

void UFirebaseInvitesConvertInvitationProxy::OnQueryCompleted(bool bSuccess)
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
