// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageReferenceGetMetadata.h"
#include "UltimateMobileKit.h"

FFirebaseStorageReferenceGetMetadata::FFirebaseStorageReferenceGetMetadata(FUltimateMobileKit* InSubsystem, const FOnFirebaseStorageReferenceGetMetadataCompleteDelegate& InDelegate, const UStorageReference* InStorageReference) 
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, StorageReference(InStorageReference)
{
}

void FFirebaseStorageReferenceGetMetadata::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseStorageReferenceGetMetadata async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid() && FirebaseStorage->IsInitialized())
		{
			NativeStorage = FirebaseStorage->GetFirebaseNativeStorage();

			if (NativeStorage.IsValid())
			{
				NativeStorageReference = MakeShareable(new firebase::storage::StorageReference(*(StorageReference->GetNativeStorageReference())));
				if (NativeStorageReference.IsValid() && NativeStorageReference->is_valid())
				{
					FetchFutureResult = NativeStorageReference->GetMetadata();
				
					return;
				}
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseStorageReferenceGetMetadata::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	if (FetchFutureResult.status() == firebase::kFutureStatusComplete)
	{
		Error = FFirebaseStorage::FirebaseErrorFromNative(static_cast<firebase::storage::Error>(FetchFutureResult.error()));

		if (FetchFutureResult.error() == firebase::storage::kErrorNone)
		{
			bWasSuccessful = true;
			const firebase::storage::Metadata* ResultMetadata = FetchFutureResult.result();
			
			if (ResultMetadata->is_valid())
			{
				StorageMetadata.Bucket = FString(ResultMetadata->bucket());
				StorageMetadata.CacheControl = FString(ResultMetadata->cache_control());
				StorageMetadata.ContentDisposition = FString(ResultMetadata->content_disposition());
				StorageMetadata.ContentEncoding = FString(ResultMetadata->content_encoding());
				StorageMetadata.ContentLanguage = FString(ResultMetadata->content_language());
				StorageMetadata.ContentType = FString(ResultMetadata->content_type());
				StorageMetadata.CreationTime = FString::Printf(TEXT("%lld"), ResultMetadata->creation_time());
				StorageMetadata.MD5Hash = FString(ResultMetadata->md5_hash());
				StorageMetadata.Generation = FString::Printf(TEXT("%lld"), ResultMetadata->generation());
				StorageMetadata.MetadataGeneration = FString::Printf(TEXT("%lld"), ResultMetadata->metadata_generation());
				StorageMetadata.Name = FString(ResultMetadata->name());
				StorageMetadata.Path = FString(ResultMetadata->path());
				StorageMetadata.SizeBytes = FString::Printf(TEXT("%lld"), ResultMetadata->size_bytes());
				StorageMetadata.UpdatedTime = FString::Printf(TEXT("%lld"), ResultMetadata->updated_time());
				StorageMetadata.IsValid = ResultMetadata->is_valid();
			}
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseStorageReferenceGetMetadata Error: %s"), *FString(FetchFutureResult.error_message()));
		}
		bIsComplete = true;
	}

	if (FetchFutureResult.status() == firebase::kFutureStatusInvalid)
	{
		bWasSuccessful = false;
		bIsComplete = true;
	}
#endif
}

void FFirebaseStorageReferenceGetMetadata::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseStorageReferenceGetMetadata async task %s, Bucket: %s, Name: %s, Path: %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"), *StorageMetadata.Bucket, *StorageMetadata.Name, *StorageMetadata.Path);

	Delegate.ExecuteIfBound(bWasSuccessful, Error, StorageMetadata);
}

void FFirebaseStorageReferenceGetMetadata::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FetchFutureResult.Release();
#endif
}
