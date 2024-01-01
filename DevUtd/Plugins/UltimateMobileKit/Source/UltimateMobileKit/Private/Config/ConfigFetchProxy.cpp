// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Config/ConfigFetchProxy.h"
#include "UltimateMobileKit.h"
#include "Config/ConfigLibrary.h"

UFirebaseConfigFetchProxy::UFirebaseConfigFetchProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseConfigFetchProxy* UFirebaseConfigFetchProxy::Fetch(const int32 CacheExpirationInSeconds)
{
	UFirebaseConfigFetchProxy* Proxy = NewObject<UFirebaseConfigFetchProxy>();
	Proxy->CacheExpirationInSeconds = CacheExpirationInSeconds;
	return Proxy;
}

void UFirebaseConfigFetchProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseConfigPtr FirebaseConfig = UltimateMobileKit->GetFirebaseConfig();

		if (FirebaseConfig.IsValid() && FirebaseConfig->IsInitialized())
		{
			FOnFirebaseConfigFetchCompleteDelegate FetchCompleteDelegate = FOnFirebaseConfigFetchCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseConfig->Fetch(FetchCompleteDelegate, CacheExpirationInSeconds);

			return;
		}
	}

	OnFailure.Broadcast();
}

void UFirebaseConfigFetchProxy::OnQueryCompleted(bool bSuccess)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast();
	}
	else
	{
		OnFailure.Broadcast();
	}
}
