// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageReferencePutFileProxy.h"
#include "UltimateMobileKit.h"

UFirebaseStorageReferencePutFileProxy::UFirebaseStorageReferencePutFileProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UFirebaseStorageReferencePutFileProxy* UFirebaseStorageReferencePutFileProxy::StorageReferencePutFile(UStorageReference* StorageReference, FString PathFile)
{
	UFirebaseStorageReferencePutFileProxy* Proxy = NewObject<UFirebaseStorageReferencePutFileProxy>();
	Proxy->StorageReference = StorageReference;
	Proxy->PathFile = PathFile;
	return Proxy;
}

void UFirebaseStorageReferencePutFileProxy::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid())
		{
			FOnFirebaseStorageReferencePutFileCompleteDelegate StorageReferencePutFileDelegate = FOnFirebaseStorageReferencePutFileCompleteDelegate::CreateUObject(this, &ThisClass::OnQueryCompleted);
			FOnFirebaseStorageReferencePutFileStartCompleteDelegate StorageReferencePutFileStartCompleteDelegate = FOnFirebaseStorageReferencePutFileStartCompleteDelegate::CreateUObject(this, &ThisClass::OnStartCompleted);

			FirebaseStorage->ReferencePutFile(StorageReference, PathFile, StorageReferencePutFileDelegate, StorageReferencePutFileStartCompleteDelegate);

			return;
		}
	}

	OnFailure.Broadcast(EFirebaseStorageError::Unknown);
}

void UFirebaseStorageReferencePutFileProxy::OnQueryCompleted(bool bSuccess, const EFirebaseStorageError& Error)
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

void UFirebaseStorageReferencePutFileProxy::OnStartCompleted(const UFirebaseStorageListener* StorageListener, const UStorageController* StorageController)
{
	OnStart.Broadcast(StorageListener, StorageController);
}
