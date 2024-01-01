// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthSignInEmailProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthSignInEmailProxy::UFirebaseAuthSignInEmailProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthSignInEmailProxy* UFirebaseAuthSignInEmailProxy::SignInWithEmailAndPassword(const FString& Email, const FString& Password)
{
	UFirebaseAuthSignInEmailProxy* Proxy = NewObject<UFirebaseAuthSignInEmailProxy>();
	Proxy->Email = Email;
	Proxy->Password = Password;
	return Proxy;
}

void UFirebaseAuthSignInEmailProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthSignInEmailCompleteDelegate SignInEmailCompleteDelegate = FOnFirebaseAuthSignInEmailCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->SignInWithEmailAndPassword(Email, Password, SignInEmailCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthSignInEmailProxy::OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error)
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
