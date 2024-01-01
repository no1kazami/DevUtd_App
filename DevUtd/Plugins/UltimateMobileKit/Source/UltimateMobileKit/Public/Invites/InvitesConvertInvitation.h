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

/** Get the (possibly still pending) results of the most recent ConvertInvitation call. */
class FFirebaseInvitesConvertInvitation : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseInvitesConvertInvitation(FUltimateMobileKit* InSubsystem, const FOnFirebaseInvitesConvertInvitationCompleteDelegate& InDelegate, const FString& InInvitationId);

	virtual FString ToString() const override { return TEXT("FirebaseInvitesConvertInvitation"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseInvitesConvertInvitationCompleteDelegate Delegate;
	const FString InvitationId;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	firebase::Future<void> FetchFutureResult;
#endif
};
