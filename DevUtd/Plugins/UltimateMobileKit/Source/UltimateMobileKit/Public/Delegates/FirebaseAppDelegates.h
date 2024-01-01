// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "FirebaseAppDelegates.generated.h"

/** Called when Firebase making Google Play available is completed */
DECLARE_DELEGATE_OneParam(FOnFirebaseMakeGooglePlayAvailableCompleteDelegate, const bool);

/** Possible availability states for Google Play services. */
UENUM(BlueprintType)
enum class EGooglePlayAvailability : uint8
{
	/** Gooogle Play services are available. */
	Available,

	/** Google Play services is disabled in Settings. */
	UnavailableDisabled,

	/** Google Play services is invalid. */
	UnavailableInvalid,

	/** Google Play services is not installed. */
	UnavailableMissing,

	/** Google Play services does not have the correct permissions. */
	UnavailablePermissions,

	/** Google Play services need to be updated. */
	UnavailableUpdateRequired,

	/** Google Play services is currently updating. */
	UnavailableUpdating,

	/** Some other error occurred. */
	UnavailableOther
};
