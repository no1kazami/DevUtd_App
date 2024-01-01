// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "Delegates/FirebaseAppDelegates.h"

#if WITH_ULTIMATEMOBILEKIT
#include "firebase/app.h"
#endif

#if WITH_ULTIMATEMOBILEKIT
typedef TSharedPtr<firebase::App, ESPMode::ThreadSafe> FFirebaseNativeAppPtr;
#endif

/** Initialization and management of Firebase application. Entry point for other modules. */
class ULTIMATEMOBILEKIT_API FFirebaseApp
{
public:
	FFirebaseApp();
	virtual ~FFirebaseApp();

#if WITH_ULTIMATEMOBILEKIT
	inline FFirebaseNativeAppPtr GetFirebaseNativeApp()
	{
		return FirebaseNativeAppPtr;
	}
#endif

	/** Initialize the Firebase Core API  */
	const bool Init();

	/** Shutdown the Firebase Core API  */
	void Shutdown();

	/** Check if Firebase Core is initialized */
	const bool IsInitialized() const;

	/** Set Firebase Core initialization state */
	void SetInitialized(const bool Initialized);

	/** Check whether Google Play services is available on this device. */
	const EGooglePlayAvailability CheckGooglePlayAvailability() const;

	/** Attempt to make Google Play services available, by installing, updating, activating, or whatever else needs to be done. */
	void MakeGooglePlayAvailable(const FOnFirebaseMakeGooglePlayAvailableCompleteDelegate& Delegate = FOnFirebaseMakeGooglePlayAvailableCompleteDelegate()) const;

private:
	bool bInitialized = false;

#if WITH_ULTIMATEMOBILEKIT
	FFirebaseNativeAppPtr FirebaseNativeAppPtr;
#endif
};
