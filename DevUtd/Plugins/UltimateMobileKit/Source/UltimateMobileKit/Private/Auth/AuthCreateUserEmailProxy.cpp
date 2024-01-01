// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthCreateUserEmailProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthCreateUserEmailProxy::UFirebaseAuthCreateUserEmailProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Email("")
	, Password("")
{
}

UFirebaseAuthCreateUserEmailProxy* UFirebaseAuthCreateUserEmailProxy::CreateUserWithEmailAndPassword(const FString& Email, const FString& Password)
{
	UFirebaseAuthCreateUserEmailProxy* Proxy = NewObject<UFirebaseAuthCreateUserEmailProxy>();
	Proxy->Email = Email;
	Proxy->Password = Password;
	return Proxy;
}

void UFirebaseAuthCreateUserEmailProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthCreateUserEmailCompleteDelegate CreateUserEmailCompleteDelegate = FOnFirebaseAuthCreateUserEmailCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->CreateUserWithEmailAndPassword(Email, Password, CreateUserEmailCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthCreateUserEmailProxy::OnQueryCompleted(const bool bSuccess, const EFirebaseAuthError& Error)
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
