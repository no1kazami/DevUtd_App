// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseInvitesDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
#include "firebase/future.h"
#include "firebase/invites.h"
#endif

class FUltimateMobileKit;

/** Start displaying the invitation UI, which will ultimately result in sending zero or more invitations. */
class FFirebaseInvitesSendInvite : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseInvitesSendInvite(FUltimateMobileKit* InSubsystem, const FOnFirebaseInvitesSendInviteCompleteDelegate& InDelegate, const FFirebaseInvite& InInvite);

	virtual FString ToString() const override { return TEXT("FirebaseInvitesSendInvite"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseInvitesSendInviteCompleteDelegate Delegate;
	FFirebaseInvite Invite;
	FFirebaseSendInviteResult InviteResult;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	firebase::Future<firebase::invites::SendInviteResult> FetchFutureResult;
#endif
};
