// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseStorageDelegates.h"
#include "StorageReferenceGetMetadataProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFirebaseGetMetadataSuccess, FFirebaseStorageMetadata, Metadata, const EFirebaseStorageError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseGetMetadataFailure, const EFirebaseStorageError&, Error);

/** Retrieves metadata associated with an object at this StorageReference */
UCLASS(MinimalAPI)
class UFirebaseStorageReferenceGetMetadataProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseGetMetadataSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseGetMetadataFailure OnFailure;

	/** Retrieves metadata associated with an object at this StorageReference */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Storage", DisplayName = "Firebase Storage Reference Get Metadata")
	static UFirebaseStorageReferenceGetMetadataProxy* StorageReferenceGetMetadata(UStorageReference* StorageReference);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseStorageError& Error, const FFirebaseStorageMetadata Metadata);

private:
	UStorageReference* StorageReference;
};
