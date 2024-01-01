// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "InvitesListener.generated.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
#include "firebase/invites.h"
#endif


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFirebaseInvitesListenerOnErrorReceived, const int32, ErrorCode, const FString, ErrorMessage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFirebaseInvitesListenerOnInviteNotReceived);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FFirebaseInvitesListenerOnInviteReceived, const FString, InvitationId, const FString, DynamicLink, EFirebaseInvitesLinkMatchStrength, MatchStrength);


class FFirebaseInvitesListener
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	: public firebase::invites::Listener
#endif
{
public:
	FFirebaseInvitesListener(FFirebaseInvitesListenerOnErrorReceived* InOnErrorReceivedEvent, FFirebaseInvitesListenerOnInviteNotReceived* InOnInviteNotReceivedEvent, FFirebaseInvitesListenerOnInviteReceived* InOnInviteReceivedEvent);
	virtual ~FFirebaseInvitesListener();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	/** Called when an error occurs trying to fetch the invitation information. */
	virtual void OnErrorReceived(int error_code, const char *error_message) override;

	/** Called when there was no invitation or dynamic link tied to opening the app. */
	virtual void OnInviteNotReceived() override;

	/** Called when an invitation is received. */
	virtual void OnInviteReceived(const char *invitation_id, const char *dynamic_link, firebase::invites::LinkMatchStrength match_strength) override;
#endif

private:
	FFirebaseInvitesListenerOnErrorReceived* OnErrorReceivedEvent;
	FFirebaseInvitesListenerOnInviteNotReceived* OnInviteNotReceivedEvent;
	FFirebaseInvitesListenerOnInviteReceived* OnInviteReceivedEvent;
};


typedef TSharedPtr<FFirebaseInvitesListener, ESPMode::ThreadSafe> FFirebaseNativeInvitesListenerPtr;

/** Class used to receive Invites and Dynamic Links. */
UCLASS()
class ULTIMATEMOBILEKIT_API UFirebaseInvitesListener : public UObject
{
public:
	GENERATED_UCLASS_BODY()

	virtual ~UFirebaseInvitesListener();

	/** Called when an error occurs trying to fetch the invitation information. */
	UPROPERTY(BlueprintAssignable)
	FFirebaseInvitesListenerOnErrorReceived OnErrorReceivedEvent;

	/** Called when there was no invitation or dynamic link tied to opening the app. */
	UPROPERTY(BlueprintAssignable)
	FFirebaseInvitesListenerOnInviteNotReceived OnInviteNotReceivedEvent;

	/** Called when an invitation is received. */
	UPROPERTY(BlueprintAssignable)
	FFirebaseInvitesListenerOnInviteReceived OnInviteReceivedEvent;

	/** Get Native Invites Listener */
	FFirebaseNativeInvitesListenerPtr GetNativeInvitesListener();

private:
	FFirebaseNativeInvitesListenerPtr NativeInvitesListener;
};
