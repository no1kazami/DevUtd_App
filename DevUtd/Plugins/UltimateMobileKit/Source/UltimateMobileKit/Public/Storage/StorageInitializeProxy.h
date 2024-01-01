// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseStorageDelegates.h"
#include "StorageInitializeProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseStorageInitializeSuccess, const EFirebaseStorageError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseStorageInitializeFailure, const EFirebaseStorageError&, Error);

/** Initialize the Firebase Storage API  */
UCLASS(MinimalAPI)
class UFirebaseStorageInitializeProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseStorageInitializeSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseStorageInitializeFailure OnFailure;

	/** Initialize the Firebase Storage API  */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Storage", DisplayName = "Firebase Storage Init")
	static UFirebaseStorageInitializeProxy* Init();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseStorageError& Error);
};
