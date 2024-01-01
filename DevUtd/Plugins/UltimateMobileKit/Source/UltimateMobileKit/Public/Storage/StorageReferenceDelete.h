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

/** Deletes the object at the current path */
class FFirebaseStorageReferenceDelete : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseStorageReferenceDelete(FUltimateMobileKit* InSubsystem, const FOnFirebaseStorageReferenceDeleteCompleteDelegate& InDelegate, const UStorageReference* InStorageReference);

	virtual FString ToString() const override { return TEXT("FirebaseStorageReferenceDelete"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseStorageReferenceDeleteCompleteDelegate Delegate;
	const UStorageReference* StorageReference;
	EFirebaseStorageError Error;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FFirebaseNativeStorageReferencePtr  NativeStorageReference;
	FFirebaseNativeStoragePtr NativeStorage;
	firebase::Future<void> FetchFutureResult;
#endif
};
