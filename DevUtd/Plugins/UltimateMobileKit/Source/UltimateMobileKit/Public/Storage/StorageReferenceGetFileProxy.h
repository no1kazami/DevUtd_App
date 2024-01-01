// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Storage/StorageController.h"
#include "StorageReferenceGetFileProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFirebaseGetFileStart, const UFirebaseStorageListener*, StorageListener, const UStorageController*, StorageController);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseGetFileSuccess, const EFirebaseStorageError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseGetFileFailure, const EFirebaseStorageError&, Error);


/** Asynchronously downloads the object from StorageReference */
UCLASS(MinimalAPI)
class UFirebaseStorageReferenceGetFileProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseGetFileStart OnStart;

	UPROPERTY(BlueprintAssignable)
	FFirebaseGetFileSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseGetFileFailure OnFailure;

	/** Asynchronously downloads the object from StorageReference */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Storage", DisplayName = "Firebase Storage Reference Get File")
	static UFirebaseStorageReferenceGetFileProxy* StorageReferenceGetFile(UStorageReference* StorageReference, FString PathFile);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseStorageError& Error);
	void OnStartCompleted(const UFirebaseStorageListener* StorageListener, const UStorageController* StorageController);

private:
	UStorageReference* StorageReference;
	FString PathFile;
};
