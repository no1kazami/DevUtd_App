// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Invites/InvitesListener.h"
#include "InvitesInitializeProxy.generated.h"


/** Initialize the Firebase Invites API  */
UCLASS(MinimalAPI)
class UFirebaseInvitesInitializeProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	/** Initialize the Firebase Invites API  */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Invites", DisplayName = "Firebase Invites Init")
	static UFirebaseInvitesInitializeProxy* Init();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess);
};
