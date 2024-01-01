// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthSignInWithGoogleProxy.h"
#include "UltimateMobileKit.h"


UFirebaseAuthSignInWithGoogleProxy::UFirebaseAuthSignInWithGoogleProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthSignInWithGoogleProxy* UFirebaseAuthSignInWithGoogleProxy::SignInWithGoogle()
{
	UFirebaseAuthSignInWithGoogleProxy* Proxy = NewObject<UFirebaseAuthSignInWithGoogleProxy>();
	return Proxy;
}

void UFirebaseAuthSignInWithGoogleProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthSignInWithGoogleCompleteDelegate SignInWithGoogleCompleteDelegate = FOnFirebaseAuthSignInWithGoogleCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->SignInWithGoogle(SignInWithGoogleCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast();
}

void UFirebaseAuthSignInWithGoogleProxy::OnQueryCompleted(bool bSuccess, const FString& IdToken, const FString& ServerAuthCode)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(IdToken, ServerAuthCode);
	}
	else
	{
		OnFailure.Broadcast();
	}
}
