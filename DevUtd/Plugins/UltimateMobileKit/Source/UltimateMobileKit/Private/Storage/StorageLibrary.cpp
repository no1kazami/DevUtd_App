// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageLibrary.h"
#include "UltimateMobileKit.h"


UUltimateMobileKitStorage::UUltimateMobileKitStorage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const bool UUltimateMobileKitStorage::IsFirebaseStorageInitialized()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid())
		{
			return FirebaseStorage->IsInitialized();
		}
	}

	return false;
}

UStorageReference* UUltimateMobileKitStorage::GetStorageReferenceToRoot()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid())
		{
			return FirebaseStorage->GetStorageReferenceToRoot();
		}
	}

	return NewObject<UStorageReference>();
}

UStorageReference* UUltimateMobileKitStorage::GetStorageReferenceFromUrl(const FString& Url)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid())
		{
			return FirebaseStorage->GetStorageReferenceFromUrl(Url);
		}
	}

	return NewObject<UStorageReference>();
}

UStorageReference* UUltimateMobileKitStorage::GetStorageReferenceFromPath(const FString& Path)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid())
		{
			return FirebaseStorage->GetStorageReferenceFromPath(Path);
		}
	}

	return NewObject<UStorageReference>();
}

const FString UUltimateMobileKitStorage::GetPlatformStoragePath()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid())
		{
			return FirebaseStorage->GetPlatformStoragePath();
		}
	}

	return FString();
}

const FString UUltimateMobileKitStorage::GetUnrealStoragePath()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid())
		{
			return FirebaseStorage->GetUnrealStoragePath();
		}
	}

	return FString();
}

const FString UUltimateMobileKitStorage::GetSaveGameStoragePath()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid())
		{
			return FirebaseStorage->GetSaveGameStoragePath();
		}
	}

	return FString();
}
