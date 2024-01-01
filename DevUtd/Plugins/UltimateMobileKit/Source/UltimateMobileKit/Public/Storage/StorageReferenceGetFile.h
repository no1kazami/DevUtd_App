// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Storage/StorageReference.h"
#include "Storage/StorageController.h"
#include "Storage/StorageListener.h"
#include "Delegates/FirebaseStorageDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
#include "firebase/future.h"
#include "firebase/storage.h"
#endif

class FUltimateMobileKit;

/** Asynchronously downloads the object from StorageReference */
class FFirebaseStorageReferenceGetFile : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseStorageReferenceGetFile(FUltimateMobileKit* InSubsystem, const FOnFirebaseStorageReferenceGetFileCompleteDelegate& InDelegate, const FOnFirebaseStorageReferenceGetFileStartCompleteDelegate& InStartDelegate, const UStorageReference* InStorageReference, const FString& InPathFile);

	virtual FString ToString() const override { return TEXT("FirebaseStorageReferenceGetFile"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseStorageReferenceGetFileCompleteDelegate Delegate;
	const FOnFirebaseStorageReferenceGetFileStartCompleteDelegate StartDelegate;
	const UStorageReference* StorageReference;
	UStorageController* StorageController;
	UFirebaseStorageListener* StorageListener;
	FString PathFile;
	EFirebaseStorageError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	TSharedPtr<std::string, ESPMode::ThreadSafe> PathFileShared;
	FFirebaseNativeStorageReferencePtr  NativeStorageReference;
	FFirebaseNativeStoragePtr NativeStorage;
	firebase::Future<size_t> FetchFutureResult;
#endif
};
