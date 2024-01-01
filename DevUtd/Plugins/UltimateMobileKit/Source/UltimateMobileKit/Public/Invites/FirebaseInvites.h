// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Delegates/FirebaseInvitesDelegates.h"
#include "Invites/InvitesListener.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
#include "firebase/invites.h"
#endif

/** Firebase Invites allows to sending personalized email and SMS invitations, on-boarding users, and measuring the impact of invitations or dynamic links. */
class ULTIMATEMOBILEKIT_API FFirebaseInvites
{
public:
	FFirebaseInvites();
	virtual ~FFirebaseInvites();

	/** Initialize the Firebase Invites API  */
	void Init(const FOnFirebaseInvitesInitializeCompleteDelegate& Delegate = FOnFirebaseInvitesInitializeCompleteDelegate());

	/** Shutdown the Firebase Invites API  */
	void Shutdown();

	/** Check if Firebase Invites is initialized */
	const bool IsInitialized() const;

	/** Set Firebase Invites initialization state */
	void SetInitialized(const bool Initialized);

	/** Get Firebase Invites Listener */
	UFirebaseInvitesListener* GetListener() const;

	/** Start displaying the invitation UI, which will ultimately result in sending zero or more invitations. */
	void SendInvite(const FFirebaseInvite Invite, const FOnFirebaseInvitesSendInviteCompleteDelegate& Delegate = FOnFirebaseInvitesSendInviteCompleteDelegate()) const;

	/** Get the (possibly still pending) results of the most recent ConvertInvitation call. */
	void ConvertInvitation(const FString& InvitationId, const FOnFirebaseInvitesConvertInvitationCompleteDelegate& Delegate = FOnFirebaseInvitesConvertInvitationCompleteDelegate()) const;

	/** Fetch any pending invites. */
	void Fetch() const;

private:
	bool bInitialized = false;

	UPROPERTY()
	UFirebaseInvitesListener* InvitesListener;
};
