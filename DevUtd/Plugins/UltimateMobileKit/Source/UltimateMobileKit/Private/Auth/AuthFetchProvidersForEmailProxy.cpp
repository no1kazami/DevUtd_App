// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthFetchProvidersForEmailProxy.h"
#include "UltimateMobileKit.h"

UFirebaseAuthFetchProvidersForEmailProxy::UFirebaseAuthFetchProvidersForEmailProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseAuthFetchProvidersForEmailProxy* UFirebaseAuthFetchProvidersForEmailProxy::FetchProvidersForEmail(const FString& Email)
{
	UFirebaseAuthFetchProvidersForEmailProxy* Proxy = NewObject<UFirebaseAuthFetchProvidersForEmailProxy>();
	Proxy->Email = Email;
	return Proxy;
}

void UFirebaseAuthFetchProvidersForEmailProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAuthPtr FirebaseAuth = UltimateMobileKit->GetFirebaseAuth();

		if (FirebaseAuth.IsValid() && FirebaseAuth->IsInitialized())
		{
			FOnFirebaseAuthFetchProvidersForEmailCompleteDelegate FetchProvidersForEmailCompleteDelegate = FOnFirebaseAuthFetchProvidersForEmailCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseAuth->FetchProvidersForEmail(Email, FetchProvidersForEmailCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseAuthError::ApiNotAvailable);
}

void UFirebaseAuthFetchProvidersForEmailProxy::OnQueryCompleted(const bool bSuccess, const EFirebaseAuthError& Error, const TArray<FString>& Providers)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(Error, Providers);
	}
	else
	{
		OnFailure.Broadcast(Error);
	}
}
