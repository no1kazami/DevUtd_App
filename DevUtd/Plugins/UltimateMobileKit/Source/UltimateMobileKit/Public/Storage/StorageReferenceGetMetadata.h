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

/** Retrieves metadata associated with an object at this StorageReference */
class FFirebaseStorageReferenceGetMetadata : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseStorageReferenceGetMetadata(FUltimateMobileKit* InSubsystem, const FOnFirebaseStorageReferenceGetMetadataCompleteDelegate& InDelegate, const UStorageReference* InStorageReference);

	virtual FString ToString() const override { return TEXT("FirebaseStorageReferenceGetMetadata"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseStorageReferenceGetMetadataCompleteDelegate Delegate;
	const UStorageReference* StorageReference;
	FFirebaseStorageMetadata StorageMetadata;
	EFirebaseStorageError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FFirebaseNativeStorageReferencePtr  NativeStorageReference;
	FFirebaseNativeStoragePtr NativeStorage;
	firebase::Future<firebase::storage::Metadata> FetchFutureResult;
#endif
};
