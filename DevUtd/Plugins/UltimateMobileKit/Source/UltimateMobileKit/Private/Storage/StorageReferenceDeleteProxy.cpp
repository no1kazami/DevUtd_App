// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageReferenceDeleteProxy.h"
#include "UltimateMobileKit.h"

UFirebaseStorageReferenceDeleteProxy::UFirebaseStorageReferenceDeleteProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseStorageReferenceDeleteProxy* UFirebaseStorageReferenceDeleteProxy::StorageReferenceDelete(UStorageReference* StorageReference)
{
	UFirebaseStorageReferenceDeleteProxy* Proxy = NewObject<UFirebaseStorageReferenceDeleteProxy>();
	Proxy->StorageReference = StorageReference;
	return Proxy;
}

void UFirebaseStorageReferenceDeleteProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid())
		{
			FOnFirebaseStorageReferenceDeleteCompleteDelegate StorageReferenceDelete = FOnFirebaseStorageReferenceDeleteCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseStorage->ReferenceDelete(StorageReference, StorageReferenceDelete);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseStorageError::Unknown);
}

void UFirebaseStorageReferenceDeleteProxy::OnQueryCompleted(bool bSuccess, const EFirebaseStorageError& Error)
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
