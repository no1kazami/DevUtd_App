// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Storage/StorageReference.h"
#include "Storage/StorageController.h"
#include "Delegates/FirebaseStorageDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
#include "firebase/future.h"
#include "firebase/storage.h"
#include "firebase/storage/metadata.h"
#endif

class FUltimateMobileKit;

/** Asynchronously uploads data to the currently specified StorageReference, without additional metadata */
class FFirebaseStorageReferencePutFile : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseStorageReferencePutFile(FUltimateMobileKit* InSubsystem, const FOnFirebaseStorageReferencePutFileCompleteDelegate& InDelegate, const FOnFirebaseStorageReferencePutFileStartCompleteDelegate& InStartDelegate, const UStorageReference* InStorageReference, const FString& InPathFile);

	virtual FString ToString() const override { return TEXT("FirebaseStorageReferencePutFile"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseStorageReferencePutFileCompleteDelegate Delegate;
	const FOnFirebaseStorageReferencePutFileStartCompleteDelegate StartDelegate;
	const UStorageReference* StorageReference;
	UStorageController* StorageController;
	UFirebaseStorageListener* StorageListener;
	FString PathFile;
	EFirebaseStorageError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	TSharedPtr<std::string, ESPMode::ThreadSafe> PathFileShared;
	FFirebaseNativeStorageReferencePtr  NativeStorageReference;
	FFirebaseNativeStoragePtr NativeStorage;
	firebase::Future<firebase::storage::Metadata> FetchFutureResult;
#endif
};
