// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthUpdatePasswordProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthUpdatePasswordProxy::UFirebaseAuthUpdatePasswordProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthUpdatePasswordProxy* UFirebaseAuthUpdatePasswordProxy::UpdatePassword(const FString& Password)
{
	UFirebaseAuthUpdatePasswordProxy* Proxy = NewObject<UFirebaseAuthUpdatePasswordProxy>();
	Proxy->Password = Password;
	return Proxy;
}

void UFirebaseAuthUpdatePasswordProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthUpdatePasswordCompleteDelegate UpdatePasswordCompleteDelegate = FOnFirebaseAuthUpdatePasswordCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->UpdatePassword(Password, UpdatePasswordCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthUpdatePasswordProxy::OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error)
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
