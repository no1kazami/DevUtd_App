// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageReferenceUpdateMetadata.h"
#include "UltimateMobileKit.h"

FFirebaseStorageReferenceUpdateMetadata::FFirebaseStorageReferenceUpdateMetadata(FUltimateMobileKit* InSubsystem, const FOnFirebaseStorageReferenceUpdateMetadataCompleteDelegate& InDelegate, const UStorageReference* InStorageReference, const FFirebaseStorageMetadataWrite InStorageMetadata)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, StorageReference(InStorageReference)
	, StorageMetadata(InStorageMetadata)
{
}

void FFirebaseStorageReferenceUpdateMetadata::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseStorageReferenceUpdateMetadata async task..."));

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
				NativeMetadata = MakeShareable(new firebase::storage::Metadata());

				if (NativeStorageReference.IsValid() && NativeStorageReference->is_valid() && NativeMetadata.IsValid())
				{
					TSharedPtr<std::string, ESPMode::ThreadSafe> CacheControlShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*StorageMetadata.CacheControl)));
					if (StorageMetadata.CacheControl.Len() > 0)
					{
						NativeMetadata->set_cache_control(*CacheControlShared);
					}

					TSharedPtr<std::string, ESPMode::ThreadSafe> ContentDispositionShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*StorageMetadata.ContentDisposition)));
					if (StorageMetadata.ContentDisposition.Len() > 0)
					{
						NativeMetadata->set_content_disposition(*ContentDispositionShared);
					}

					TSharedPtr<std::string, ESPMode::ThreadSafe> ContentEncodingShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*StorageMetadata.ContentEncoding)));
					if (StorageMetadata.ContentEncoding.Len() > 0)
					{
						NativeMetadata->set_content_encoding(*ContentEncodingShared);
					}

					TSharedPtr<std::string, ESPMode::ThreadSafe> ContentLanguageShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*StorageMetadata.ContentLanguage)));
					if (StorageMetadata.ContentLanguage.Len() > 0)
					{
						NativeMetadata->set_content_language(*ContentLanguageShared);
					}

					TSharedPtr<std::string, ESPMode::ThreadSafe> ContentTypeShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*StorageMetadata.ContentType)));
					if (StorageMetadata.ContentType.Len() > 0)
					{
						NativeMetadata->set_content_type(*ContentTypeShared);
					}

					auto CustomMetadata = NativeMetadata->custom_metadata();
					CustomMetadata->insert(std::make_pair("", ""));

					FetchFutureResult = NativeStorageReference->UpdateMetadata(*NativeMetadata);

					return;
				}
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseStorageReferenceUpdateMetadata::Tick()
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
				StorageMetadataResult.Bucket = FString(ResultMetadata->bucket());
				StorageMetadataResult.CacheControl = FString(ResultMetadata->cache_control());
				StorageMetadataResult.ContentDisposition = FString(ResultMetadata->content_disposition());
				StorageMetadataResult.ContentEncoding = FString(ResultMetadata->content_encoding());
				StorageMetadataResult.ContentLanguage = FString(ResultMetadata->content_language());
				StorageMetadataResult.ContentType = FString(ResultMetadata->content_type());
				StorageMetadataResult.CreationTime = FString::Printf(TEXT("%lld"), ResultMetadata->creation_time());
				StorageMetadataResult.MD5Hash = FString(ResultMetadata->md5_hash());
				StorageMetadataResult.Generation = FString::Printf(TEXT("%lld"), ResultMetadata->generation());
				StorageMetadataResult.MetadataGeneration = FString::Printf(TEXT("%lld"), ResultMetadata->metadata_generation());
				StorageMetadataResult.Name = FString(ResultMetadata->name());
				StorageMetadataResult.Path = FString(ResultMetadata->path());
				StorageMetadataResult.SizeBytes = FString::Printf(TEXT("%lld"), ResultMetadata->size_bytes());
				StorageMetadataResult.UpdatedTime = FString::Printf(TEXT("%lld"), ResultMetadata->updated_time());
				StorageMetadataResult.IsValid = ResultMetadata->is_valid();
			}
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseStorageReferenceUpdateMetadata Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseStorageReferenceUpdateMetadata::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseStorageReferenceUpdateMetadata async task %s, Bucket: %s, Name: %s, Path: %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"), *StorageMetadataResult.Bucket, *StorageMetadataResult.Name, *StorageMetadataResult.Path);

	Delegate.ExecuteIfBound(bWasSuccessful, Error, StorageMetadataResult);
}

void FFirebaseStorageReferenceUpdateMetadata::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FetchFutureResult.Release();
#endif
}
