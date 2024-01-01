// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Storage/StorageReference.h"
#include "Storage/StorageController.h"
#include "Delegates/FirebaseStorageDelegates.h"
#include "StorageReferencePutFileProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFirebasePutFileStart, const UFirebaseStorageListener*, StorageListener, const UStorageController*, StorageController);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebasePutFileSuccess, const EFirebaseStorageError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebasePutFileFailure, const EFirebaseStorageError&, Error);

/** Asynchronously uploads data to the currently specified StorageReference, without additional metadata */
UCLASS(MinimalAPI)
class UFirebaseStorageReferencePutFileProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebasePutFileStart OnStart;

	UPROPERTY(BlueprintAssignable)
	FFirebasePutFileSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebasePutFileFailure OnFailure;

	/** Asynchronously uploads data to the currently specified StorageReference, without additional metadata */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Storage", DisplayName = "Firebase Storage Reference Put File")
	static UFirebaseStorageReferencePutFileProxy* StorageReferencePutFile(UStorageReference* StorageReference, FString PathFile);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseStorageError& Error);
	void OnStartCompleted(const UFirebaseStorageListener* StorageListener, const UStorageController* StorageController);

private:
	UStorageReference* StorageReference;
	FString PathFile;
};
