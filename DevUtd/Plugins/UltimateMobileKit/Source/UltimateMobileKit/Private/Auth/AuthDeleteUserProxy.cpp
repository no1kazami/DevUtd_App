// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthDeleteUserProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthDeleteUserProxy::UFirebaseAuthDeleteUserProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthDeleteUserProxy* UFirebaseAuthDeleteUserProxy::DeleteUser()
{
	UFirebaseAuthDeleteUserProxy* Proxy = NewObject<UFirebaseAuthDeleteUserProxy>();
	return Proxy;
}

void UFirebaseAuthDeleteUserProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthDeleteUserCompleteDelegate DeleteUserCompleteDelegate = FOnFirebaseAuthDeleteUserCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->DeleteUser(DeleteUserCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthDeleteUserProxy::OnQueryCompleted(const bool bSuccess, const EFirebaseAuthError& Error)
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
