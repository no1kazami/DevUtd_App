// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Invites/InvitesListener.h"
#include "InvitesLibrary.generated.h"

/** Blueprint implementation of FirebaseInvites. Firebase Invites allows to sending personalized email and SMS invitations, on-boarding users, and measuring the impact of invitations or dynamic links. */
UCLASS()
class ULTIMATEMOBILEKIT_API UUltimateMobileKitInvites : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** Check if Firebase Invites is initialized */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Invites")
	static const bool IsFirebaseInvitesInitialized();

	/** Fetch any pending invites. */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Invites", DisplayName = "Firebase Invites Fetch")
	static void Fetch();

	/** Get listener used to receive Invites and Dynamic Links */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Invites", DisplayName = "Firebase Invites Get Listener")
	static UFirebaseInvitesListener* GetListener();
};
