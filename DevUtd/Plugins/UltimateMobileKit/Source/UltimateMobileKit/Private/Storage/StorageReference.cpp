// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageReference.h"

UStorageReference::UStorageReference(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, FullPath("")
	, bIsValid(false)
{
}

UStorageReference* UStorageReference::Child(const FString& Path)
{
	UStorageReference* NewStorageReference = NewObject<UStorageReference>();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	bool bIsModuleInitialized = false;
	if (UltimateMobileKit)
	{
		bIsModuleInitialized = UltimateMobileKit->GetFirebaseStorage()->IsInitialized();
	}

	if (bIsModuleInitialized)
	{
		FFirebaseNativeStorageReferencePtr CurrentNativeStorageReference = GetNativeStorageReference();
		FFirebaseNativeStorageReferencePtr NewNativeStorageReference = MakeShareable(new firebase::storage::StorageReference(CurrentNativeStorageReference->Child(TCHAR_TO_UTF8(*Path))));
		NewStorageReference->RegisterStorageFullPath(NewNativeStorageReference);

		UE_LOG(LogUltimateMobileKit, Display, TEXT("Child of Storage Reference in path %s is %s"), *Path, *NewStorageReference->FullPath);
	}
#endif

	return NewStorageReference;
}

UStorageReference* UStorageReference::GetParent()
{
	UStorageReference* NewStorageReference = NewObject<UStorageReference>();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	bool bIsModuleInitialized = false;
	if (UltimateMobileKit)
	{
		bIsModuleInitialized = UltimateMobileKit->GetFirebaseStorage()->IsInitialized();
	}

	if (bIsModuleInitialized)
	{
		FFirebaseNativeStorageReferencePtr CurrentNativeStorageReference = GetNativeStorageReference();
		FFirebaseNativeStorageReferencePtr NewNativeStorageReference = MakeShareable(new firebase::storage::StorageReference(CurrentNativeStorageReference->GetParent()));
		NewStorageReference->RegisterStorageFullPath(NewNativeStorageReference);

		UE_LOG(LogUltimateMobileKit, Display, TEXT("Parent of Storage Reference is %s"), *NewStorageReference->FullPath);
	}
#endif

	return NewStorageReference;
}

bool UStorageReference::IsValid()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	bool bIsModuleInitialized = false;
	if (UltimateMobileKit)
	{
		bIsModuleInitialized = UltimateMobileKit->GetFirebaseStorage()->IsInitialized();
	}

	if (bIsModuleInitialized)
	{
		FFirebaseNativeStorageReferencePtr CurrentNativeStorageReference = GetNativeStorageReference();
		bool bStorageIsValid = (bIsValid && CurrentNativeStorageReference.IsValid() && CurrentNativeStorageReference->is_valid());

		UE_LOG(LogUltimateMobileKit, Display, TEXT("Storage Reference is %s"), bStorageIsValid ? TEXT("valid") : TEXT("is not valid"));

		return bStorageIsValid;
	}

	UE_LOG(LogUltimateMobileKit, Display, TEXT("Storage Reference retrieving failed"));

#endif

	return false;
}

const FString UStorageReference::GetBucket()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	bool bIsModuleInitialized = false;
	if (UltimateMobileKit)
	{
		bIsModuleInitialized = UltimateMobileKit->GetFirebaseStorage()->IsInitialized();
	}

	if (bIsModuleInitialized)
	{
		FFirebaseNativeStorageReferencePtr CurrentNativeStorageReference = GetNativeStorageReference();
		if (CurrentNativeStorageReference.IsValid() && CurrentNativeStorageReference->is_valid())
		{
			FString BucketName = FString(CurrentNativeStorageReference->bucket().c_str());

			UE_LOG(LogUltimateMobileKit, Display, TEXT("Bucket of Storage Reference is %s"), *BucketName);

			return BucketName;
		}
	}

	UE_LOG(LogUltimateMobileKit, Display, TEXT("Bucket of Storage Reference retrieving failed"));

#endif

	return FString();
}

const FString UStorageReference::GetFullPath()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	bool bIsModuleInitialized = false;
	if (UltimateMobileKit)
	{
		bIsModuleInitialized = UltimateMobileKit->GetFirebaseStorage()->IsInitialized();
	}

	if (bIsModuleInitialized)
	{
		FFirebaseNativeStorageReferencePtr CurrentNativeStorageReference = GetNativeStorageReference();
		if (CurrentNativeStorageReference.IsValid() && CurrentNativeStorageReference->is_valid())
		{
			FString FullPathStorage = FString(CurrentNativeStorageReference->full_path().c_str());

			UE_LOG(LogUltimateMobileKit, Display, TEXT("Full Path of Storage Reference is %s"), *FullPathStorage);

			return FullPathStorage;
		}
	}

	UE_LOG(LogUltimateMobileKit, Display, TEXT("Full Path of Storage Reference retrieving failed"));

#endif

	return FString();
}

const FString UStorageReference::GetShortName()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	bool bIsModuleInitialized = false;
	if (UltimateMobileKit)
	{
		bIsModuleInitialized = UltimateMobileKit->GetFirebaseStorage()->IsInitialized();
	}

	if (bIsModuleInitialized)
	{
		FFirebaseNativeStorageReferencePtr CurrentNativeStorageReference = GetNativeStorageReference();
		if (CurrentNativeStorageReference.IsValid() && CurrentNativeStorageReference->is_valid())
		{
			FString ShortName = FString(CurrentNativeStorageReference->name().c_str());

			UE_LOG(LogUltimateMobileKit, Display, TEXT("Short Name of Storage Reference is %s"), *ShortName);

			return ShortName;
		}
	}

	UE_LOG(LogUltimateMobileKit, Display, TEXT("Short Name of Storage Reference retrieving failed"));

#endif

	return FString();
}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
FFirebaseNativeStorageReferencePtr UStorageReference::GetNativeStorageReference() const
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();
	return MakeShareable(new firebase::storage::StorageReference(FirebaseStorage->GetFirebaseNativeStorage()->GetReference(TCHAR_TO_UTF8(*FullPath))));
}

bool UStorageReference::RegisterStorageFullPath(FFirebaseNativeStorageReferencePtr NewStorageReference)
{
	if (NewStorageReference.IsValid() && NewStorageReference->is_valid())
	{
		bIsValid = true;
		FullPath = FString(NewStorageReference->full_path().c_str());
	}
	else
	{
		bIsValid = false;
	}

	return bIsValid;
}

#endif
