// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseStorageDelegates.h"
#include "StorageReferenceDeleteProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseReferenceDeleteSuccess, const EFirebaseStorageError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseReferenceDeleteFailure, const EFirebaseStorageError&, Error);

/** Deletes the object at the current path */
UCLASS(MinimalAPI)
class UFirebaseStorageReferenceDeleteProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseReferenceDeleteSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseReferenceDeleteFailure OnFailure;

	/** Deletes the object at the current path */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Storage", DisplayName = "Firebase Storage Reference Delete")
	static UFirebaseStorageReferenceDeleteProxy* StorageReferenceDelete(UStorageReference* StorageReference);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseStorageError& Error);

private:
	UStorageReference* StorageReference;
};
