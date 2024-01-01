// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthSendEmailVerificationProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthSendEmailVerificationProxy::UFirebaseAuthSendEmailVerificationProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthSendEmailVerificationProxy* UFirebaseAuthSendEmailVerificationProxy::SendEmailVerification()
{
	UFirebaseAuthSendEmailVerificationProxy* Proxy = NewObject<UFirebaseAuthSendEmailVerificationProxy>();
	return Proxy;
}

void UFirebaseAuthSendEmailVerificationProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthSendEmailVerificationCompleteDelegate SendEmailVerificationCompleteDelegate = FOnFirebaseAuthSendEmailVerificationCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->SendEmailVerification(SendEmailVerificationCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthSendEmailVerificationProxy::OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error)
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
