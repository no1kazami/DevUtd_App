// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthFetchProvidersForEmailProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFirebaseAuthFetchProvidersForEmailSuccess, const EFirebaseAuthError&, Error, const TArray<FString>&, Providers);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthFetchProvidersForEmailFailure, const EFirebaseAuthError&, Error);

/** Asynchronously requests the IDPs (identity providers) that can be used for the given email address */
UCLASS(MinimalAPI)
class UFirebaseAuthFetchProvidersForEmailProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthFetchProvidersForEmailSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthFetchProvidersForEmailFailure OnFailure;

	/** Asynchronously requests the IDPs (identity providers) that can be used for the given email address */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Fetch Providers For Email")
	static UFirebaseAuthFetchProvidersForEmailProxy* FetchProvidersForEmail(const FString& Email);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error, const TArray<FString>& Providers);

private:
	FString Email;
};
