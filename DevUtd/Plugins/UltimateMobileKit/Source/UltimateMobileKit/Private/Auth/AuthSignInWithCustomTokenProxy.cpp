// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthSignInWithCustomTokenProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthSignInWithCustomTokenProxy::UFirebaseAuthSignInWithCustomTokenProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthSignInWithCustomTokenProxy* UFirebaseAuthSignInWithCustomTokenProxy::SignInWithCustomToken(const FString& Token)
{
	UFirebaseAuthSignInWithCustomTokenProxy* Proxy = NewObject<UFirebaseAuthSignInWithCustomTokenProxy>();
	Proxy->Token = Token;
	return Proxy;
}

void UFirebaseAuthSignInWithCustomTokenProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthSignInWithCustomTokenCompleteDelegate SignInWithCustomTokenCompleteDelegate = FOnFirebaseAuthSignInWithCustomTokenCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->SignInWithCustomToken(Token, SignInWithCustomTokenCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthSignInWithCustomTokenProxy::OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error)
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
