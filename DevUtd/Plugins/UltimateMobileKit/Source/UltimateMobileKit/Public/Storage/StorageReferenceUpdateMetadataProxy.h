// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseStorageDelegates.h"
#include "StorageReferenceUpdateMetadataProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFirebaseUpdateMetadataSuccess, FFirebaseStorageMetadata, Metadata, const EFirebaseStorageError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseUpdateMetadataFailure, const EFirebaseStorageError&, Error);


/** Updates the metadata associated with this StorageReference */
UCLASS(MinimalAPI)
class UFirebaseStorageReferenceUpdateMetadataProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseUpdateMetadataSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseUpdateMetadataFailure OnFailure;

	/** Updates the metadata associated with this StorageReference */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Storage", DisplayName = "Firebase Storage Reference Update Metadata")
	static UFirebaseStorageReferenceUpdateMetadataProxy* StorageReferenceUpdateMetadata(UStorageReference* StorageReference, FFirebaseStorageMetadataWrite StorageMetadata);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseStorageError& Error, const FFirebaseStorageMetadata Metadata);

private:
	UStorageReference* StorageReference;
	FFirebaseStorageMetadataWrite StorageMetadata;
};
