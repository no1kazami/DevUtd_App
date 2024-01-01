// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseInstanceIdDelegates.h"
#include "InstanceIdGetTokenProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFirebaseInstanceIdGetTokenSuccess, const FString&, Token, const EFirebaseInstanceIdError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseInstanceIdGetTokenFailure, const EFirebaseInstanceIdError&, Error);

/** Returns a token that authorizes an Entity to perform an action on behalf of the application identified by Instance ID. */
UCLASS(MinimalAPI)
class UFirebaseInstanceIdGetTokenProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseInstanceIdGetTokenSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseInstanceIdGetTokenFailure OnFailure;

	/** Returns a token that authorizes an Entity to perform an action on behalf of the application identified by Instance ID. */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Instance Id", DisplayName = "Firebase Instance Id Get Token")
	static UFirebaseInstanceIdGetTokenProxy* GetToken();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseInstanceIdError& Error, const FString& Token);
};
