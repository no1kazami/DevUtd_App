// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthReloadUserProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthReloadUserProxy::UFirebaseAuthReloadUserProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthReloadUserProxy* UFirebaseAuthReloadUserProxy::ReloadUser()
{
	UFirebaseAuthReloadUserProxy* Proxy = NewObject<UFirebaseAuthReloadUserProxy>();
	return Proxy;
}

void UFirebaseAuthReloadUserProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthReloadUserCompleteDelegate ReloadUserCompleteDelegate = FOnFirebaseAuthReloadUserCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->ReloadUser(ReloadUserCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthReloadUserProxy::OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error)
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
