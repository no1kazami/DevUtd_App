// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "LinksInitializeProxy.generated.h"

/** Initialize the Firebase Dynamic Links API  */
UCLASS(MinimalAPI)
class UFirebaseLinksInitializeProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	/** Initialize the Firebase Dynamic Links API  */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Dynamic Links", DisplayName = "Firebase Dynamic Links Init")
	static UFirebaseLinksInitializeProxy* Init(UFirebaseLinksListener* Listener);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess);

private:
	UFirebaseLinksListener* LinksListener;
};
