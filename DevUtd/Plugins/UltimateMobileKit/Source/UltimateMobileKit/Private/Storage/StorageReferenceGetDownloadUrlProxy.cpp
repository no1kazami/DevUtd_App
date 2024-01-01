// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageReferenceGetDownloadUrlProxy.h"
#include "UltimateMobileKit.h"

UFirebaseStorageReferenceGetDownloadUrlProxy::UFirebaseStorageReferenceGetDownloadUrlProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseStorageReferenceGetDownloadUrlProxy* UFirebaseStorageReferenceGetDownloadUrlProxy::StorageReferenceGetDownloadUrl(UStorageReference* StorageReference)
{
	UFirebaseStorageReferenceGetDownloadUrlProxy* Proxy = NewObject<UFirebaseStorageReferenceGetDownloadUrlProxy>();
	Proxy->StorageReference = StorageReference;
	return Proxy;
}

void UFirebaseStorageReferenceGetDownloadUrlProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid())
		{
			FOnFirebaseStorageReferenceGetDownloadUrlCompleteDelegate StorageReferenceGetDownloadUrlDelegate = FOnFirebaseStorageReferenceGetDownloadUrlCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);

			FirebaseStorage->ReferenceGetDownloadUrl(StorageReference, StorageReferenceGetDownloadUrlDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseStorageError::Unknown);
}

void UFirebaseStorageReferenceGetDownloadUrlProxy::OnQueryCompleted(bool bSuccess, const EFirebaseStorageError& Error, const FString DownloadUrl)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(DownloadUrl, Error);
	}
	else
	{
		OnFailure.Broadcast(Error);
	}
}
