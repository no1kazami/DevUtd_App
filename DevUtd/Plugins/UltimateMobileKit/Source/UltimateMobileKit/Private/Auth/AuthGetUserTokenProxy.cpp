// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthGetUserTokenProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthGetUserTokenProxy::UFirebaseAuthGetUserTokenProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthGetUserTokenProxy* UFirebaseAuthGetUserTokenProxy::GetUserToken(const bool ForceRefresh /*= false*/)
{
	UFirebaseAuthGetUserTokenProxy* Proxy = NewObject<UFirebaseAuthGetUserTokenProxy>();
	Proxy->ForceRefresh = ForceRefresh;
	return Proxy;
}

void UFirebaseAuthGetUserTokenProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthGetUserTokenCompleteDelegate GetUserTokenCompleteDelegate = FOnFirebaseAuthGetUserTokenCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->GetUserToken(GetUserTokenCompleteDelegate, ForceRefresh);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthGetUserTokenProxy::OnQueryCompleted(const bool bSuccess, const EFirebaseAuthError& Error, const FString& Token)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(Error, Token);
	}
	else
	{
		OnFailure.Broadcast(Error);
	}
}
