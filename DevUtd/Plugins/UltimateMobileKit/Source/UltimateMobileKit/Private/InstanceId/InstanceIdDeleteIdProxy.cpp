// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "InstanceId/InstanceIdDeleteIdProxy.h"
#include "UltimateMobileKit.h"

UFirebaseInstanceIdDeleteIdProxy::UFirebaseInstanceIdDeleteIdProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseInstanceIdDeleteIdProxy* UFirebaseInstanceIdDeleteIdProxy::DeleteId()
{
	UFirebaseInstanceIdDeleteIdProxy* Proxy = NewObject<UFirebaseInstanceIdDeleteIdProxy>();
	return Proxy;
}

void UFirebaseInstanceIdDeleteIdProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInstanceIdPtr FirebaseInstanceId = UltimateMobileKit->GetFirebaseInstanceId();

		if (FirebaseInstanceId.IsValid())
		{
			FOnFirebaseInstanceIdDeleteIdCompleteDelegate DeleteIdCompleteDelegate = FOnFirebaseInstanceIdDeleteIdCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseInstanceId->DeleteId(DeleteIdCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseInstanceIdError::Unknown);
}

void UFirebaseInstanceIdDeleteIdProxy::OnQueryCompleted(bool bSuccess, const EFirebaseInstanceIdError& Error)
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
