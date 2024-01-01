// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthPasswordResetProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthPasswordResetProxy::UFirebaseAuthPasswordResetProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthPasswordResetProxy* UFirebaseAuthPasswordResetProxy::SendPasswordResetEmail(const FString& Email)
{
	UFirebaseAuthPasswordResetProxy* Proxy = NewObject<UFirebaseAuthPasswordResetProxy>();
	Proxy->Email = Email;
	return Proxy;
}

void UFirebaseAuthPasswordResetProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthPasswordResetCompleteDelegate PasswordResetCompleteDelegate = FOnFirebaseAuthPasswordResetCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->SendPasswordResetEmail(Email, PasswordResetCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthPasswordResetProxy::OnQueryCompleted(const bool bSuccess, const EFirebaseAuthError& Error)
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
