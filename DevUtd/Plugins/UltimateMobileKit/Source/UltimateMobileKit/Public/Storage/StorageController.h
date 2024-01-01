// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "StorageController.generated.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
#include "firebase/storage/controller.h"
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
typedef TSharedPtr<firebase::storage::Controller, ESPMode::ThreadSafe> FFirebaseNativeStorageControllerPtr;
#endif

/** Controls an ongoing operation, allowing the caller to Pause, Resume or Cancel an ongoing download or upload */
UCLASS()
class ULTIMATEMOBILEKIT_API UStorageController : public UObject
{
	GENERATED_UCLASS_BODY()

	/** Cancels the operation currently in progress */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Storage")
	bool Cancel();

	/** Pauses the operation currently in progress */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Storage")
	bool Pause();

	/** Resumes the operation that is paused */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Storage")
	bool Resume();

	/** Returns true if the operation is paused */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Storage")
	bool IsPaused();

	/** Returns true if this Controller is valid, false if it is not valid */ 
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Storage")
	bool IsValid();

	/** Returns a progress of requested operation */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Storage")
	float GetProgress();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	/** Returns native Storage Controller */
	FFirebaseNativeStorageControllerPtr GetNativeStorageController();
#endif

private:
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FFirebaseNativeStorageControllerPtr NativeStorageController;
#endif
};
