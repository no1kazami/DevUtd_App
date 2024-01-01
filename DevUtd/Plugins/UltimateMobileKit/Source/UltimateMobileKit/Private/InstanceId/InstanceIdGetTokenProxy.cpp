// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "InstanceId/InstanceIdGetTokenProxy.h"
#include "UltimateMobileKit.h"

UFirebaseInstanceIdGetTokenProxy::UFirebaseInstanceIdGetTokenProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseInstanceIdGetTokenProxy* UFirebaseInstanceIdGetTokenProxy::GetToken()
{
	UFirebaseInstanceIdGetTokenProxy* Proxy = NewObject<UFirebaseInstanceIdGetTokenProxy>();
	return Proxy;
}

void UFirebaseInstanceIdGetTokenProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInstanceIdPtr FirebaseInstanceId = UltimateMobileKit->GetFirebaseInstanceId();

		if (FirebaseInstanceId.IsValid())
		{
			FOnFirebaseInstanceIdGetTokenCompleteDelegate GetTokenCompleteDelegate = FOnFirebaseInstanceIdGetTokenCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseInstanceId->GetToken(GetTokenCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseInstanceIdError::Unknown);
}

void UFirebaseInstanceIdGetTokenProxy::OnQueryCompleted(bool bSuccess, const EFirebaseInstanceIdError& Error, const FString& Token)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(Token, Error);
	}
	else
	{
		OnFailure.Broadcast(Error);
	}
}
