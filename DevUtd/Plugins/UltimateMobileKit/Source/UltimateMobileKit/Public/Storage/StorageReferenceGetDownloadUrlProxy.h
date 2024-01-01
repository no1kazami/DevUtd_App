// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseStorageDelegates.h"
#include "StorageReferenceGetDownloadUrlProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFirebaseGetDownloadUrlSuccess, const FString&, DownloadUrl, const EFirebaseStorageError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseGetDownloadUrlSFailure, const EFirebaseStorageError&, Error);

/** Asynchronously retrieves a long lived download URL with a revokable token */
UCLASS(MinimalAPI)
class UFirebaseStorageReferenceGetDownloadUrlProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseGetDownloadUrlSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseGetDownloadUrlSFailure OnFailure;

	/** Asynchronously retrieves a long lived download URL with a revokable token */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Storage", DisplayName = "Firebase Storage Reference Get Download Url")
	static UFirebaseStorageReferenceGetDownloadUrlProxy* StorageReferenceGetDownloadUrl(UStorageReference* StorageReference);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseStorageError& Error, const FString DownloadUrl);

private:
	UStorageReference* StorageReference;
};
