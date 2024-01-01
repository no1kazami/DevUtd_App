// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Storage/StorageReference.h"
#include "Delegates/FirebaseStorageDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
#include "firebase/future.h"
#include "firebase/storage.h"
#include "firebase/storage/metadata.h"
#endif

class FUltimateMobileKit;

/** Updates the metadata associated with this StorageReference */
class FFirebaseStorageReferenceUpdateMetadata : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseStorageReferenceUpdateMetadata(FUltimateMobileKit* InSubsystem, const FOnFirebaseStorageReferenceUpdateMetadataCompleteDelegate& InDelegate, const UStorageReference* InStorageReference, const FFirebaseStorageMetadataWrite InStorageMetadata);

	virtual FString ToString() const override { return TEXT("FirebaseStorageReferenceUpdateMetadata"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseStorageReferenceUpdateMetadataCompleteDelegate Delegate;
	const UStorageReference* StorageReference;
	FFirebaseStorageMetadataWrite StorageMetadata;
	FFirebaseStorageMetadata StorageMetadataResult;
	EFirebaseStorageError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FFirebaseNativeStorageReferencePtr  NativeStorageReference;
	TSharedPtr<firebase::storage::Metadata, ESPMode::ThreadSafe>  NativeMetadata;

	FFirebaseNativeStoragePtr NativeStorage;
	firebase::Future<firebase::storage::Metadata> FetchFutureResult;
#endif
};
