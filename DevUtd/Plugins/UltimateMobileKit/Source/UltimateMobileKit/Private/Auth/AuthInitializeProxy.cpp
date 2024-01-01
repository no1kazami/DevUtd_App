// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthInitializeProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthInitializeProxy::UFirebaseAuthInitializeProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthInitializeProxy* UFirebaseAuthInitializeProxy::Init()
{
	UFirebaseAuthInitializeProxy* Proxy = NewObject<UFirebaseAuthInitializeProxy>();
	return Proxy;
}

void UFirebaseAuthInitializeProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid())
		{
			FOnFirebaseAuthInitializeCompleteDelegate InitializeCompleteDelegate = FOnFirebaseAuthInitializeCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->Init(InitializeCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthInitializeProxy::OnQueryCompleted(const bool bSuccess, const EFirebaseAuthError& Error)
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
