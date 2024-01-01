// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "InstanceId/InstanceIdGetIdProxy.h"
#include "UltimateMobileKit.h"

UFirebaseInstanceIdGetIdProxy::UFirebaseInstanceIdGetIdProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseInstanceIdGetIdProxy* UFirebaseInstanceIdGetIdProxy::GetId()
{
	UFirebaseInstanceIdGetIdProxy* Proxy = NewObject<UFirebaseInstanceIdGetIdProxy>();
	return Proxy;
}

void UFirebaseInstanceIdGetIdProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInstanceIdPtr FirebaseInstanceId = UltimateMobileKit->GetFirebaseInstanceId();

		if (FirebaseInstanceId.IsValid())
		{
			FOnFirebaseInstanceIdGetIdCompleteDelegate GetIdCompleteDelegate = FOnFirebaseInstanceIdGetIdCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseInstanceId->GetId(GetIdCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseInstanceIdError::Unknown);
}

void UFirebaseInstanceIdGetIdProxy::OnQueryCompleted(bool bSuccess, const EFirebaseInstanceIdError& Error, const FString& Id)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(Id, Error);
	}
	else
	{
		OnFailure.Broadcast(Error);
	}
}
