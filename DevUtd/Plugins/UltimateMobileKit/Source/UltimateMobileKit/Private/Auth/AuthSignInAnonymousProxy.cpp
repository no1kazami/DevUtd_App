// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthSignInAnonymousProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthSignInAnonymousProxy::UFirebaseAuthSignInAnonymousProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthSignInAnonymousProxy* UFirebaseAuthSignInAnonymousProxy::SignInAnonymously()
{
	UFirebaseAuthSignInAnonymousProxy* Proxy = NewObject<UFirebaseAuthSignInAnonymousProxy>();
	return Proxy;
}

void UFirebaseAuthSignInAnonymousProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthSignInAnonymousCompleteDelegate SignInAnonymousCompleteDelegate = FOnFirebaseAuthSignInAnonymousCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->SignInAnonymously(SignInAnonymousCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthSignInAnonymousProxy::OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error)
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
