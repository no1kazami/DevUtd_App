// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "FirebaseInstanceIdDelegates.generated.h"

/** Error code returned by Firebase Instance Id functions. */
UENUM(BlueprintType)
enum class EFirebaseInstanceIdError : uint8
{
	/** The operation was a success, no error occurred. */
	None,

	/** An unknown error occurred. */
	Unknown,

	/** Request could not be validated from this client. */
	Authentication,

	/** Instance ID service cannot be accessed. */
	NoAccess,

	/** Request to instance ID backend timed out. */
	Timeout,

	/** No network available to reach the servers. */
	Network,

	/** A similar operation is in progress so aborting this one. */
	OperationInProgress,

	/** Some of the parameters of the request were invalid. */
	InvalidRequest
};

/** Called when Firebase Instance Id module is initialized */
DECLARE_DELEGATE_TwoParams(FOnFirebaseInstanceIdInitializeCompleteDelegate, const bool, const EFirebaseInstanceIdError&);

/** Called when Firebase retrieving Instance Id Token is completed */
DECLARE_DELEGATE_ThreeParams(FOnFirebaseInstanceIdGetTokenCompleteDelegate, const bool, const EFirebaseInstanceIdError&, const FString&);

/** Called when Firebase retrieving Instance Id is completed */
DECLARE_DELEGATE_ThreeParams(FOnFirebaseInstanceIdGetIdCompleteDelegate, const bool, const EFirebaseInstanceIdError&, const FString&);

/** Called when Firebase Instance Id Token deleting is completed */
DECLARE_DELEGATE_TwoParams(FOnFirebaseInstanceIdDeleteTokenCompleteDelegate, const bool, const EFirebaseInstanceIdError&);

/** Called when Firebase Instance Id deleting is completed */
DECLARE_DELEGATE_TwoParams(FOnFirebaseInstanceIdDeleteIdCompleteDelegate, const bool, const EFirebaseInstanceIdError&);
