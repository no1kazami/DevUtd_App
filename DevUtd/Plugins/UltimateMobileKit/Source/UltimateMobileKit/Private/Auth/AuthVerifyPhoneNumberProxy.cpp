// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthVerifyPhoneNumberProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthVerifyPhoneNumberProxy::UFirebaseAuthVerifyPhoneNumberProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthVerifyPhoneNumberProxy* UFirebaseAuthVerifyPhoneNumberProxy::VerifyPhoneNumber(const FString& PhoneNumber)
{
	UFirebaseAuthVerifyPhoneNumberProxy* Proxy = NewObject<UFirebaseAuthVerifyPhoneNumberProxy>();
	Proxy->PhoneNumber = PhoneNumber;
	return Proxy;
}

void UFirebaseAuthVerifyPhoneNumberProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthVerifyPhoneNumberCompleteDelegate PhoneNumberCompleteDelegate = FOnFirebaseAuthVerifyPhoneNumberCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->VerifyPhoneNumber(PhoneNumber, PhoneNumberCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthVerifyPhoneNumberProxy::OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error, const FString& VerificationId, const UFirebaseCredential* Credential)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(Error, VerificationId, Credential);
	}
	else
	{
		OnFailure.Broadcast(Error);
	}
}
