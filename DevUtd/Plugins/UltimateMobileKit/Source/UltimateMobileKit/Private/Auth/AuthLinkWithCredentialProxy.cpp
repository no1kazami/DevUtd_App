// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthLinkWithCredentialProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthLinkWithCredentialProxy::UFirebaseAuthLinkWithCredentialProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthLinkWithCredentialProxy* UFirebaseAuthLinkWithCredentialProxy::LinkWithCredentialProxy(const UFirebaseCredential* Credential)
{
	UFirebaseAuthLinkWithCredentialProxy* Proxy = NewObject<UFirebaseAuthLinkWithCredentialProxy>();
	Proxy->Credential = Credential;
	return Proxy;
}

void UFirebaseAuthLinkWithCredentialProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthLinkWithCredentialCompleteDelegate LinkWithCredentialCompleteDelegate = FOnFirebaseAuthLinkWithCredentialCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->LinkWithCredential(Credential, LinkWithCredentialCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthLinkWithCredentialProxy::OnQueryCompleted(const bool bSuccess, const EFirebaseAuthError& Error)
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
