// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "StorageReference.generated.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
#include "firebase/storage/storage_reference.h"
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
typedef TSharedPtr<firebase::storage::StorageReference, ESPMode::ThreadSafe> FFirebaseNativeStorageReferencePtr;
#endif

/** Represents a reference to a Cloud Storage object */
UCLASS()
class ULTIMATEMOBILEKIT_API UStorageReference : public UObject
{
	GENERATED_UCLASS_BODY()

	/** Gets a reference to a location relative to this one */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Storage", meta = (DisplayName = "Child"))
	UStorageReference* Child(const FString& Path);

	/** Returns a new instance of StorageReference pointing to the parent location or null if this instance references the root location */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Storage", meta = (DisplayName = "Get Parent"))
	UStorageReference* GetParent();

	/** Returns true if this StorageReference is valid, false if it is not valid */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Storage", meta = (DisplayName = "Is Valid"))
	bool IsValid();

	/** Return the Google Cloud Storage bucket that holds this object */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Storage", meta = (DisplayName = "Get Bucket"))
	const FString GetBucket();

	/** Return the full path of the storage reference, not including the Google Cloud Storage bucket */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Storage", meta = (DisplayName = "Get Full Path"))
	const FString GetFullPath();

	/** Returns the short name of this object */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Storage", meta = (DisplayName = "Get Short Name"))
	const FString GetShortName();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	/** Returns native reference to the Storage */
	FFirebaseNativeStorageReferencePtr GetNativeStorageReference() const;

	/** Register full path to the Storage */
	bool RegisterStorageFullPath(FFirebaseNativeStorageReferencePtr NewStorageReference);
#endif

private:
	FString FullPath;
	bool bIsValid;
};
