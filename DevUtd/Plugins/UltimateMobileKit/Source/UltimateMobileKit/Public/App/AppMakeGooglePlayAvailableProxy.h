// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "AppMakeGooglePlayAvailableProxy.generated.h"

/** Refreshes the data for this user */
UCLASS(MinimalAPI)
class UFirebaseAppMakeGooglePlayAvailableProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	/** Attempt to make Google Play services available, by installing, updating, activating, or whatever else needs to be done. */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|App", DisplayName = "Firebase Make Google Play Available")
	static UFirebaseAppMakeGooglePlayAvailableProxy* MakeGooglePlayAvailable();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess);
};
