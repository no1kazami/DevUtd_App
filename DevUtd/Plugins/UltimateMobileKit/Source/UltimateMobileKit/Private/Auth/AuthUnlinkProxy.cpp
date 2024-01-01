// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthUnlinkProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthUnlinkProxy::UFirebaseAuthUnlinkProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthUnlinkProxy* UFirebaseAuthUnlinkProxy::Unlink(const EFirebaseProvider Provider)
{
	UFirebaseAuthUnlinkProxy* Proxy = NewObject<UFirebaseAuthUnlinkProxy>();
	Proxy->Provider = Provider;
	return Proxy;
}

void UFirebaseAuthUnlinkProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthUnlinkCompleteDelegate UnlinkCompleteDelegate = FOnFirebaseAuthUnlinkCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->Unlink(Provider, UnlinkCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthUnlinkProxy::OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error)
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
