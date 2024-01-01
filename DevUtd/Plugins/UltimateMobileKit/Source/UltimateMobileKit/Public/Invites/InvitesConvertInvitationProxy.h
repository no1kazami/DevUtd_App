// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseInvitesDelegates.h"
#include "InvitesConvertInvitationProxy.generated.h"

/** Get the (possibly still pending) results of the most recent ConvertInvitation call. */
UCLASS(MinimalAPI)
class UFirebaseInvitesConvertInvitationProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	/** Get the (possibly still pending) results of the most recent ConvertInvitation call. */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Invites", DisplayName = "Firebase Invites Convert Invitation")
	static UFirebaseInvitesConvertInvitationProxy* ConvertInvitation(const FString& InvitationId);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess);

private:
	FString InvitationId;
};
