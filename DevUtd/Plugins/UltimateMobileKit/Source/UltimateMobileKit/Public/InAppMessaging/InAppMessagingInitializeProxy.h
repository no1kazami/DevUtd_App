// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseInAppMessagingDelegates.h"
#include "InAppMessagingInitializeProxy.generated.h"

/** Initialize the Firebase In-App Messaging API  */
UCLASS(MinimalAPI)
class UFirebaseInAppMessagingInitializeProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	/** Initialize the Firebase In-App Messaging API  */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|In-App Messaging", DisplayName = "Firebase In-App Messaging Init")
	static UFirebaseInAppMessagingInitializeProxy* Init();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess);
};
