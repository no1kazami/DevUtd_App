// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Storage/StorageReference.h"
#include "Delegates/FirebaseStorageDelegates.h"
#include "Storage/StorageController.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
#include "firebase/storage.h"
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
typedef TSharedPtr<firebase::storage::Storage, ESPMode::ThreadSafe> FFirebaseNativeStoragePtr;
#endif

/** Firebase Storage allows to store and share images, audio, video, or other user-generated content. It allows to download and upload files. */
class ULTIMATEMOBILEKIT_API FFirebaseStorage
{
public:
	FFirebaseStorage();
	virtual ~FFirebaseStorage();

	/** Initialize the Firebase Storage API  */
	void Init(const FOnFirebaseStorageInitializeCompleteDelegate& Delegate = FOnFirebaseStorageInitializeCompleteDelegate());

	/** Shutdown the Firebase Storage API  */
	void Shutdown();

	/** Check if Firebase Storage is initialized */
	const bool IsInitialized() const;

	/** Set Firebase Storage initialization state */
	void SetInitialized(const bool Initialized);

	/** Register Firebase Storage services */
	const bool RegisterService();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	inline FFirebaseNativeStoragePtr GetFirebaseNativeStorage() const
	{
		return FirebaseNativeStoragePtr;
	}

	/** Convert Native Firebase Error to Unreal Firebase Error */
	static EFirebaseStorageError FirebaseErrorFromNative(const firebase::storage::Error& NativeError);
#endif

	/** Get a path to the game storage on specific platform */
	const FString GetPlatformStoragePath() const;

	/** Get a path to the Unreal storage on specific platform */
	const FString GetUnrealStoragePath() const;

	/** Get a path to the save game storage on specific platform */
	const FString GetSaveGameStoragePath() const;

	/** Get a StorageReference to the root of the database */
	UStorageReference* GetStorageReferenceToRoot() const;

	/** Get a StorageReference for the provided URL */
	UStorageReference* GetStorageReferenceFromUrl(const FString& Url) const;

	/** Get a StorageReference for the specified path */
	UStorageReference* GetStorageReferenceFromPath(const FString& Path) const;

	/** Deletes the object at the current path */
	void ReferenceDelete(const UStorageReference* StorageReference, const FOnFirebaseStorageReferenceDeleteCompleteDelegate& Delegate = FOnFirebaseStorageReferenceDeleteCompleteDelegate()) const;

	/** Asynchronously retrieves a long lived download URL with a revokable token */
	void ReferenceGetDownloadUrl(const UStorageReference* StorageReference, const FOnFirebaseStorageReferenceGetDownloadUrlCompleteDelegate& Delegate = FOnFirebaseStorageReferenceGetDownloadUrlCompleteDelegate()) const;

	/** Asynchronously downloads the object from StorageReference */
	void ReferenceGetFile(const UStorageReference* StorageReference, const FString& PathFile, const FOnFirebaseStorageReferenceGetFileCompleteDelegate& Delegate = FOnFirebaseStorageReferenceGetFileCompleteDelegate(), const FOnFirebaseStorageReferenceGetFileStartCompleteDelegate& StartDelegate = FOnFirebaseStorageReferenceGetFileStartCompleteDelegate()) const;

	/** Retrieves metadata associated with an object at this StorageReference */
	void ReferenceGetMetadata(const UStorageReference* StorageReference, const FOnFirebaseStorageReferenceGetMetadataCompleteDelegate& Delegate = FOnFirebaseStorageReferenceGetMetadataCompleteDelegate()) const;

	/** Asynchronously uploads data to the currently specified StorageReference, without additional metadata */
	void ReferencePutFile(const UStorageReference* StorageReference, const FString& PathFile, const FOnFirebaseStorageReferencePutFileCompleteDelegate& Delegate = FOnFirebaseStorageReferencePutFileCompleteDelegate(), const FOnFirebaseStorageReferencePutFileStartCompleteDelegate& StartDelegate = FOnFirebaseStorageReferencePutFileStartCompleteDelegate()) const;

	/** Updates the metadata associated with this StorageReference */
	void ReferenceUpdateMetadata(const UStorageReference* StorageReference, const FFirebaseStorageMetadataWrite StorageMetadata, const FOnFirebaseStorageReferenceUpdateMetadataCompleteDelegate& Delegate = FOnFirebaseStorageReferenceUpdateMetadataCompleteDelegate()) const;

private:
	bool bInitialized = false;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FFirebaseNativeStoragePtr FirebaseNativeStoragePtr;
#endif
};
