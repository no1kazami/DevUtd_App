// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "ConfigFetchProxy.generated.h"

/** Fetches config data from the server */
UCLASS(MinimalAPI)
class UFirebaseConfigFetchProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	/** Fetches config data from the server */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Remote Config", DisplayName = "Firebase Remote Config Fetch")
	static UFirebaseConfigFetchProxy* Fetch(const int32 CacheExpirationInSeconds = 0);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess);

private:
	int32 CacheExpirationInSeconds;
};
