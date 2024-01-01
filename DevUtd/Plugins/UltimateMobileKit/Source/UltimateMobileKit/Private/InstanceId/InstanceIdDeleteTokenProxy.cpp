// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "InstanceId/InstanceIdDeleteTokenProxy.h"
#include "UltimateMobileKit.h"

UFirebaseInstanceIdDeleteTokenProxy::UFirebaseInstanceIdDeleteTokenProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseInstanceIdDeleteTokenProxy* UFirebaseInstanceIdDeleteTokenProxy::DeleteToken()
{
	UFirebaseInstanceIdDeleteTokenProxy* Proxy = NewObject<UFirebaseInstanceIdDeleteTokenProxy>();
	return Proxy;
}

void UFirebaseInstanceIdDeleteTokenProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInstanceIdPtr FirebaseInstanceId = UltimateMobileKit->GetFirebaseInstanceId();

		if (FirebaseInstanceId.IsValid())
		{
			FOnFirebaseInstanceIdDeleteTokenCompleteDelegate DeleteTokenCompleteDelegate = FOnFirebaseInstanceIdDeleteTokenCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseInstanceId->DeleteToken(DeleteTokenCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseInstanceIdError::Unknown);
}

void UFirebaseInstanceIdDeleteTokenProxy::OnQueryCompleted(bool bSuccess, const EFirebaseInstanceIdError& Error)
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
