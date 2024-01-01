// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageInitializeProxy.h"
#include "UltimateMobileKit.h"

UFirebaseStorageInitializeProxy::UFirebaseStorageInitializeProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseStorageInitializeProxy* UFirebaseStorageInitializeProxy::Init()
{
	UFirebaseStorageInitializeProxy* Proxy = NewObject<UFirebaseStorageInitializeProxy>();
	return Proxy;
}

void UFirebaseStorageInitializeProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid())
		{
			FOnFirebaseStorageInitializeCompleteDelegate InitializeCompleteDelegate = FOnFirebaseStorageInitializeCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseStorage->Init(InitializeCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseStorageError::Unknown);
}

void UFirebaseStorageInitializeProxy::OnQueryCompleted(bool bSuccess, const EFirebaseStorageError& Error)
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
