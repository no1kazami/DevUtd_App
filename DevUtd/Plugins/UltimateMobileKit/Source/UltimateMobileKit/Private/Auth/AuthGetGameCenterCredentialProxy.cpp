// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthGetGameCenterCredentialProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthGetGameCenterCredentialProxy::UFirebaseAuthGetGameCenterCredentialProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthGetGameCenterCredentialProxy* UFirebaseAuthGetGameCenterCredentialProxy::GameCenterCredential()
{
	UFirebaseAuthGetGameCenterCredentialProxy* Proxy = NewObject<UFirebaseAuthGetGameCenterCredentialProxy>();
	return Proxy;
}

void UFirebaseAuthGetGameCenterCredentialProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthGetGameCenterCredentialCompleteDelegate GetGameCenterCredentialCompleteDelegate = FOnFirebaseAuthGetGameCenterCredentialCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->GetGameCenterCredential(GetGameCenterCredentialCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthGetGameCenterCredentialProxy::OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error, const UFirebaseCredential* Credential)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(Error, Credential);
	}
	else
	{
		OnFailure.Broadcast(Error);
	}
}
