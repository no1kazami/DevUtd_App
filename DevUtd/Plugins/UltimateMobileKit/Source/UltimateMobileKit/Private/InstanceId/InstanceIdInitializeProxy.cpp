// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "InstanceId/InstanceIdInitializeProxy.h"
#include "UltimateMobileKit.h"

UFirebaseInstanceIdInitializeProxy::UFirebaseInstanceIdInitializeProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseInstanceIdInitializeProxy* UFirebaseInstanceIdInitializeProxy::Init()
{
	UFirebaseInstanceIdInitializeProxy* Proxy = NewObject<UFirebaseInstanceIdInitializeProxy>();
	return Proxy;
}

void UFirebaseInstanceIdInitializeProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInstanceIdPtr FirebaseInstanceId = UltimateMobileKit->GetFirebaseInstanceId();

		if (FirebaseInstanceId.IsValid())
		{
			FOnFirebaseInstanceIdInitializeCompleteDelegate InitializeCompleteDelegate = FOnFirebaseInstanceIdInitializeCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseInstanceId->Init(InitializeCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseInstanceIdError::Unknown);
}

void UFirebaseInstanceIdInitializeProxy::OnQueryCompleted(bool bSuccess, const EFirebaseInstanceIdError& Error)
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
