// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "Storage/StorageController.h"
#include "Storage/StorageListener.h"
#include "FirebaseStorageDelegates.generated.h"

/** Error code returned by Firebase Storage functions. */
UENUM(BlueprintType)
enum class EFirebaseStorageError : uint8
{
	/** The operation was a success, no error occurred. */
	None,

	/** An unknown error occurred. */
	Unknown,

	/** No object exists at the desired reference. */
	ObjectNotFound,

	/** No bucket is configured for Cloud Storage. */
	BucketNotFound,

	/** No project is configured for Cloud Storage. */
	ProjectNotFound,

	/** Quota on your Cloud Storage bucket has been exceeded. */
	QuotaExceeded,

	/** User is unauthenticated. */
	Unauthenticated,

	/** User is not authorized to perform the desired action. */
	Unauthorized,

	/** The maximum time limit on an operation (upload, download, delete, etc.) has been exceeded. */
	RetryLimitExceeded,

	/** File on the client does not match the checksum of the file recieved by the server. */
	NonMatchingChecksum,

	/** Size of the downloaded file exceeds the amount of memory allocated for the download. */
	DownloadSizeExceeded,

	/** User cancelled the operation. */
	Cancelled
};

/** Metadata stores default attributes such as size and content type */
USTRUCT(BlueprintType)
struct FFirebaseStorageMetadata
{
	GENERATED_USTRUCT_BODY()

	/** The owning Google Cloud Storage bucket for the StorageReference */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString Bucket;

	/** The Cache Control setting of the StorageReference */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString CacheControl;

	/** The content disposition of the StorageReference */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString ContentDisposition;

	/** The content encoding for the StorageReference */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString ContentEncoding;

	/** The content language for the StorageReference */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString ContentLanguage;

	/** The content type of the StorageReference */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString ContentType;

	/** The time the StorageReference was created in milliseconds since the epoch */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString CreationTime;;

	/** A version String indicating what version of the StorageReference */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString Generation;

	/** MD5 hash of the data; encoded using base64. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString MD5Hash;

	/** A version String indicating the version of this StorageMetadata */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString MetadataGeneration;

	/** A simple name of the StorageReference object */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString Name;

	/** The path of the StorageReference object */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString Path;

	/** The stored Size in bytes of the StorageReference object */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString SizeBytes;

	/** The time the StorageReference was last updated in milliseconds since the epoch */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString UpdatedTime;

	/** True if this Metadata is valid, false if it is not valid */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	bool IsValid;

	FFirebaseStorageMetadata()
	{
		Bucket = FString("");
		CacheControl = FString("");
		ContentDisposition = FString("");
		ContentEncoding = FString("");
		ContentLanguage = FString("");
		ContentType = FString("");
		CreationTime = 0;
		Generation = 0;
		MetadataGeneration = 0;
		Name = FString("");
		Path = FString("");
		SizeBytes = 0;
		UpdatedTime = 0;
		IsValid = false;
	}
};

/** Metadata stores default attributes such as size and content type */
USTRUCT(BlueprintType)
struct FFirebaseStorageMetadataWrite
{
	GENERATED_USTRUCT_BODY()

	/** The Cache Control setting of the StorageReference */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString CacheControl;

	/** The content disposition of the StorageReference */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString ContentDisposition;

	/** The content encoding for the StorageReference */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString ContentEncoding;

	/** The content language for the StorageReference */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString ContentLanguage;

	/** The content type of the StorageReference */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Storage")
	FString ContentType;

	FFirebaseStorageMetadataWrite()
	{
		CacheControl = FString("");
		ContentDisposition = FString("");
		ContentEncoding = FString("");
		ContentLanguage = FString("");
		ContentType = FString("");
	}
};

/** Called when Firebase Storage module is initialized */
DECLARE_DELEGATE_TwoParams(FOnFirebaseStorageInitializeCompleteDelegate, const bool, const EFirebaseStorageError&);

/** Called when the object at the current path is deleted */
DECLARE_DELEGATE_TwoParams(FOnFirebaseStorageReferenceDeleteCompleteDelegate, const bool, const EFirebaseStorageError&);

/** Called when a long lived download URL with a revokable token is retrieved */
DECLARE_DELEGATE_ThreeParams(FOnFirebaseStorageReferenceGetDownloadUrlCompleteDelegate, const bool, const EFirebaseStorageError&, const FString);

/** Called when the referenced file is downloaded */
DECLARE_DELEGATE_TwoParams(FOnFirebaseStorageReferenceGetFileCompleteDelegate, const bool, const EFirebaseStorageError&);

/** Called when file downloading is started*/
DECLARE_DELEGATE_TwoParams(FOnFirebaseStorageReferenceGetFileStartCompleteDelegate, const UFirebaseStorageListener*, const UStorageController*);

/** Called when metadata associated with an object is retrieved */
DECLARE_DELEGATE_ThreeParams(FOnFirebaseStorageReferenceGetMetadataCompleteDelegate, const bool, const EFirebaseStorageError&, const FFirebaseStorageMetadata);

/** Called when file is uploaded to the Firebase Storage */
DECLARE_DELEGATE_TwoParams(FOnFirebaseStorageReferencePutFileCompleteDelegate, const bool, const EFirebaseStorageError&);

/** Called when file uploading is started */
DECLARE_DELEGATE_TwoParams(FOnFirebaseStorageReferencePutFileStartCompleteDelegate, const UFirebaseStorageListener*, const UStorageController*);

/** Called when metadata associated with StorageReference is updated */
DECLARE_DELEGATE_ThreeParams(FOnFirebaseStorageReferenceUpdateMetadataCompleteDelegate, const bool, const EFirebaseStorageError&, const FFirebaseStorageMetadata);
