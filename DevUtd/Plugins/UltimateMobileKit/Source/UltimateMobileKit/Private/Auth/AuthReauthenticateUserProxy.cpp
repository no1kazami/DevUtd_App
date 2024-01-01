// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthReauthenticateUserProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthReauthenticateUserProxy::UFirebaseAuthReauthenticateUserProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthReauthenticateUserProxy* UFirebaseAuthReauthenticateUserProxy::ReauthenticateUser(const UFirebaseCredential* Credential)
{
	UFirebaseAuthReauthenticateUserProxy* Proxy = NewObject<UFirebaseAuthReauthenticateUserProxy>();
	Proxy->Credential = Credential;
	return Proxy;
}

void UFirebaseAuthReauthenticateUserProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthReauthenticateUserCompleteDelegate ReauthenticateUserCompleteDelegate = FOnFirebaseAuthReauthenticateUserCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->ReauthenticateUser(Credential, ReauthenticateUserCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthReauthenticateUserProxy::OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error)
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
