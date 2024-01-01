// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageReferenceGetMetadataProxy.h"
#include "UltimateMobileKit.h"

UFirebaseStorageReferenceGetMetadataProxy::UFirebaseStorageReferenceGetMetadataProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseStorageReferenceGetMetadataProxy* UFirebaseStorageReferenceGetMetadataProxy::StorageReferenceGetMetadata(UStorageReference* StorageReference)
{
	UFirebaseStorageReferenceGetMetadataProxy* Proxy = NewObject<UFirebaseStorageReferenceGetMetadataProxy>();
	Proxy->StorageReference = StorageReference;
	return Proxy;
}

void UFirebaseStorageReferenceGetMetadataProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid())
		{
			FOnFirebaseStorageReferenceGetMetadataCompleteDelegate StorageReferenceGetMetadataDelegate = FOnFirebaseStorageReferenceGetMetadataCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseStorage->ReferenceGetMetadata(StorageReference, StorageReferenceGetMetadataDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseStorageError::Unknown);
}

void UFirebaseStorageReferenceGetMetadataProxy::OnQueryCompleted(bool bSuccess, const EFirebaseStorageError& Error, const FFirebaseStorageMetadata Metadata)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(Metadata, Error);
	}
	else
	{
		OnFailure.Broadcast(Error);
	}
}
