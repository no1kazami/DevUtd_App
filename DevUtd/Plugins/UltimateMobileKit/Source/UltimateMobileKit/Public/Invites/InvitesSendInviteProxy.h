// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseInvitesDelegates.h"
#include "InvitesSendInviteProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseSendInviteSuccess, FFirebaseSendInviteResult, InviteResult);

/** Start displaying the invitation UI, which will ultimately result in sending zero or more invitations. */
UCLASS(MinimalAPI)
class UFirebaseInvitesSendInviteProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseSendInviteSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	/** Start displaying the invitation UI, which will ultimately result in sending zero or more invitations. */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Invites", DisplayName = "Firebase Invites Send Invite")
	static UFirebaseInvitesSendInviteProxy* SendInvite(const FFirebaseInvite Invite);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const FFirebaseSendInviteResult InviteResult);

private:
	FFirebaseInvite Invite;
};
