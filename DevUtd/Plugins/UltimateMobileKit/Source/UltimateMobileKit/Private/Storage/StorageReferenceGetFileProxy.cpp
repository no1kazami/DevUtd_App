// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageReferenceGetFileProxy.h"
#include "UltimateMobileKit.h"

UFirebaseStorageReferenceGetFileProxy::UFirebaseStorageReferenceGetFileProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseStorageReferenceGetFileProxy* UFirebaseStorageReferenceGetFileProxy::StorageReferenceGetFile(UStorageReference* StorageReference, FString PathFile)
{
	UFirebaseStorageReferenceGetFileProxy* Proxy = NewObject<UFirebaseStorageReferenceGetFileProxy>();
	Proxy->StorageReference = StorageReference;
	Proxy->PathFile = PathFile;
	return Proxy;
}

void UFirebaseStorageReferenceGetFileProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid())
		{
			FOnFirebaseStorageReferenceGetFileCompleteDelegate StorageReferenceGetFileDelegate = FOnFirebaseStorageReferenceGetFileCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);
			FOnFirebaseStorageReferenceGetFileStartCompleteDelegate StorageReferenceGetFileStartCompleteDelegate = FOnFirebaseStorageReferenceGetFileStartCompleteDelegate::CreateUObject(this, &ThisClass::OnStartCompleted);

			FirebaseStorage->ReferenceGetFile(StorageReference, PathFile, StorageReferenceGetFileDelegate, StorageReferenceGetFileStartCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseStorageError::Unknown);
}

void UFirebaseStorageReferenceGetFileProxy::OnQueryCompleted(bool bSuccess, const EFirebaseStorageError& Error)
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

void UFirebaseStorageReferenceGetFileProxy::OnStartCompleted(const UFirebaseStorageListener* StorageListener, const UStorageController* StorageController)
{
	OnStart.Broadcast(StorageListener, StorageController);
}
