// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Storage/StorageReference.h"
#include "Delegates/FirebaseStorageDelegates.h"
#include "StorageLibrary.generated.h"

/** Blueprint implementation of FirebaseStorage. Firebase Storage allows to store and share images, audio, video, or other user-generated content. It allows to download and upload files. */
UCLASS()
class ULTIMATEMOBILEKIT_API UUltimateMobileKitStorage : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** Check if Firebase Storage is initialized */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Storage")
	static const bool IsFirebaseStorageInitialized();

	/** Get a StorageReference to the root of the database */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Storage", DisplayName = "Firebase Storage Get Storage Reference To Root")
	static UStorageReference* GetStorageReferenceToRoot();

	/** Get a StorageReference for the provided URL */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Storage", DisplayName = "Firebase Storage Get Storage Reference From Url")
	static UStorageReference* GetStorageReferenceFromUrl(const FString& Url);

	/** Get a StorageReference for the specified path */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Storage", DisplayName = "Firebase Storage Get Storage Reference From Path")
	static UStorageReference* GetStorageReferenceFromPath(const FString& Path);

	/** Get a path to the game storage on specific platform */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Storage", DisplayName = "Firebase Storage Get Platform Storage Path")
	static const FString GetPlatformStoragePath();

	/** Get a path to the Unreal storage on specific platform */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Storage", DisplayName = "Firebase Storage Get Unreal Storage Path")
	static const FString GetUnrealStoragePath();

	/** Get a path to the save game storage on specific platform */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Storage", DisplayName = "Firebase Storage Get Save Game Storage Path")
	static const FString GetSaveGameStoragePath();
};
