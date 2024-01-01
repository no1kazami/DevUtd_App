// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageReferenceUpdateMetadataProxy.h"
#include "UltimateMobileKit.h"

UFirebaseStorageReferenceUpdateMetadataProxy::UFirebaseStorageReferenceUpdateMetadataProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseStorageReferenceUpdateMetadataProxy* UFirebaseStorageReferenceUpdateMetadataProxy::StorageReferenceUpdateMetadata(UStorageReference* StorageReference, FFirebaseStorageMetadataWrite StorageMetadata)
{
	UFirebaseStorageReferenceUpdateMetadataProxy* Proxy = NewObject<UFirebaseStorageReferenceUpdateMetadataProxy>();
	Proxy->StorageReference = StorageReference;
	Proxy->StorageMetadata = StorageMetadata;
	return Proxy;
}

void UFirebaseStorageReferenceUpdateMetadataProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid())
		{
			FOnFirebaseStorageReferenceUpdateMetadataCompleteDelegate StorageReferenceUpdateMetadataDelegate = FOnFirebaseStorageReferenceUpdateMetadataCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseStorage->ReferenceUpdateMetadata(StorageReference, StorageMetadata, StorageReferenceUpdateMetadataDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseStorageError::Unknown);
}

void UFirebaseStorageReferenceUpdateMetadataProxy::OnQueryCompleted(bool bSuccess, const EFirebaseStorageError& Error, const FFirebaseStorageMetadata Metadata)
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
