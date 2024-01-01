// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthSignInWithCredentialProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthSignInWithCredentialProxy::UFirebaseAuthSignInWithCredentialProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthSignInWithCredentialProxy* UFirebaseAuthSignInWithCredentialProxy::SignInWithCredential(const UFirebaseCredential* Credential)
{
	UFirebaseAuthSignInWithCredentialProxy* Proxy = NewObject<UFirebaseAuthSignInWithCredentialProxy>();
	Proxy->Credential = Credential;
	return Proxy;
}

void UFirebaseAuthSignInWithCredentialProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthSignInWithCredentialCompleteDelegate SignInWithCredentialCompleteDelegate = FOnFirebaseAuthSignInWithCredentialCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->SignInWithCredential(Credential, SignInWithCredentialCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthSignInWithCredentialProxy::OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error)
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
