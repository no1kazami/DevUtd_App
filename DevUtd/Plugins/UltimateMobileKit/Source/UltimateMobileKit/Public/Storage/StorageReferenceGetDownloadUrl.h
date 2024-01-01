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
#endif

class FUltimateMobileKit;

/** Asynchronously retrieves a long lived download URL with a revokable token */
class FFirebaseStorageReferenceGetDownloadUrl : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseStorageReferenceGetDownloadUrl(FUltimateMobileKit* InSubsystem, const FOnFirebaseStorageReferenceGetDownloadUrlCompleteDelegate& InDelegate, const UStorageReference* InStorageReference);

	virtual FString ToString() const override { return TEXT("FirebaseStorageReferenceGetDownloadUrl"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseStorageReferenceGetDownloadUrlCompleteDelegate Delegate;
	const UStorageReference* StorageReference;
	FString DownloadUrl;
	EFirebaseStorageError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FFirebaseNativeStorageReferencePtr  NativeStorageReference;
	FFirebaseNativeStoragePtr NativeStorage;
	firebase::Future<std::string> FetchFutureResult;
#endif
};
