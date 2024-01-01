// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "ConfigInitializeProxy.generated.h"

/** Initialize the Firebase Config API  */
UCLASS(MinimalAPI)
class UFirebaseConfigInitializeProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;
	
	/** Initialize the Firebase Config API  */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "DefaultParameters"), Category = "Ultimate Mobile Kit|Remote Config", DisplayName = "Firebase Remote Config Init")
	static UFirebaseConfigInitializeProxy* Init(const TArray<UFirebaseVariant*> DefaultParameters, const FString& ConfigNamespace);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess);

private:
	TArray<UFirebaseVariant*> DefaultParameters;
	FString ConfigNamespace;
};
