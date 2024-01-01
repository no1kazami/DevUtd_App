// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "Delegates/FirebaseMessagingDelegates.h"
#include "UltimateMobileKitComponent.generated.h"

/**
* Handles asynchronous responses from Ultimate Mobile Kit requests
*/
UCLASS(ClassGroup = Mobile, HideCategories = (Activation, "Components|Activation", Collision), meta = (BlueprintSpawnableComponent), DisplayName = "Ultimate Mobile Kit")
class ULTIMATEMOBILEKIT_API UUltimateMobileKitComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void OnRegister() override;
	void OnUnregister() override;

	DECLARE_MULTICAST_DELEGATE_OneParam(FUltimateMobileKit_UserSignedInDelegate, const FFirebaseUser&);
	DECLARE_MULTICAST_DELEGATE(FUltimateMobileKit_UserSignedOutDelegate);
	DECLARE_MULTICAST_DELEGATE_OneParam(FUltimateMobileKit_UserIdTokenChangedDelegate, const FFirebaseUser&);
	DECLARE_MULTICAST_DELEGATE_OneParam(FUltimateMobileKit_MessageReceivedDelegate, const FFirebaseMessage&);
	DECLARE_MULTICAST_DELEGATE_OneParam(FUltimateMobileKit_TokenReceivedDelegate, const FString&);

	/** Called on the client when user signed in (Firebase Authentication) */
	static FUltimateMobileKit_UserSignedInDelegate UserSignedInDelegate;

	/** Called on the client when user signed out (Firebase Authentication) */
	static FUltimateMobileKit_UserSignedOutDelegate UserSignedOutDelegate;

	/** Called when there is a change in the current user's token (Firebase Authentication) */
	static FUltimateMobileKit_UserIdTokenChangedDelegate UserIdTokenChangedDelegate;

	/** Called on the client when a message arrives (Firebase Messaging) */
	static FUltimateMobileKit_MessageReceivedDelegate MessageReceivedDelegate;

	/** Called on the client when a registration token arrives (Firebase Messaging) */
	static FUltimateMobileKit_TokenReceivedDelegate TokenReceivedDelegate;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUltimateMobileKit_UserSignedInDynamicDelegate, const FFirebaseUser&, User);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUltimateMobileKit_UserSignedOutDynamicDelegate);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUltimateMobileKit_UserIdTokenChangedDynamicDelegate, const FFirebaseUser&, User);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUltimateMobileKit_MessageReceivedDynamicDelegate, const FFirebaseMessage&, Message);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUltimateMobileKit_TokenReceivedDynamicDelegate, const FString&, Token);

	/** Called on the client when user signed in (Firebase Authentication) */
	UPROPERTY(BlueprintAssignable)
	FUltimateMobileKit_UserSignedInDynamicDelegate UserSignedIn;

	/** Called on the client when user signed out (Firebase Authentication) */
	UPROPERTY(BlueprintAssignable)
	FUltimateMobileKit_UserSignedOutDynamicDelegate UserSignedOut;

	/** Called when there is a change in the current user's token (Firebase Authentication) */
	UPROPERTY(BlueprintAssignable)
	FUltimateMobileKit_UserIdTokenChangedDynamicDelegate UserIdTokenChanged;

	/** Called on the client when a message arrives (Firebase Messaging) */
	UPROPERTY(BlueprintAssignable)
	FUltimateMobileKit_MessageReceivedDynamicDelegate MessageReceived;

	/** Called on the client when a registration token arrives (Firebase Messaging) */
	UPROPERTY(BlueprintAssignable)
	FUltimateMobileKit_TokenReceivedDynamicDelegate TokenReceived;

private:
	void UserSignedIn_Handler(const FFirebaseUser& User);
	void UserSignedOut_Handler();
	void UserIdTokenChanged_Handler(const FFirebaseUser& User);
	void MessageReceived_Handler(const FFirebaseMessage& Message);
	void TokenReceived_Handler(const FString& Token);
};
