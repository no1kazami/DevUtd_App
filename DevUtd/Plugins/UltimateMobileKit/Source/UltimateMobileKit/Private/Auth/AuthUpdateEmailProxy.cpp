// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthUpdateEmailProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthUpdateEmailProxy::UFirebaseAuthUpdateEmailProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthUpdateEmailProxy* UFirebaseAuthUpdateEmailProxy::UpdateEmail(const FString& Email)
{
	UFirebaseAuthUpdateEmailProxy* Proxy = NewObject<UFirebaseAuthUpdateEmailProxy>();
	Proxy->Email = Email;
	return Proxy;
}

void UFirebaseAuthUpdateEmailProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthUpdateEmailCompleteDelegate UpdateEmailCompleteDelegate = FOnFirebaseAuthUpdateEmailCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->UpdateEmail(Email, UpdateEmailCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthUpdateEmailProxy::OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error)
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
