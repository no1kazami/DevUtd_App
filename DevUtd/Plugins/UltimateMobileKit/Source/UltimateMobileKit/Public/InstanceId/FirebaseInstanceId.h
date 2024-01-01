// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "Delegates/FirebaseInstanceIdDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
#include "firebase/instance_id.h"
#include "firebase/util.h"
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
typedef TSharedPtr<firebase::instance_id::InstanceId, ESPMode::ThreadSafe> FFirebaseNativeInstanceIdPtr;
#endif

/** Instance ID provides a unique identifier for each app instance and a mechanism to authenticate and authorize actions (for example, sending a FCM message). */
class ULTIMATEMOBILEKIT_API FFirebaseInstanceId
{
public:
	FFirebaseInstanceId();
	virtual ~FFirebaseInstanceId();

	/** Initialize the Firebase Instance Id API  */
	void Init(const FOnFirebaseInstanceIdInitializeCompleteDelegate& Delegate = FOnFirebaseInstanceIdInitializeCompleteDelegate());

	/** Shutdown the Firebase Instance Id API  */
	void Shutdown();

	/** Check if Firebase Instance Id is initialized */
	const bool IsInitialized() const;

	/** Set Firebase Instance Id initialization state */
	void SetInitialized(const bool Initialized);

	/** Register Firebase Instance Id services */
	const bool RegisterService();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	inline FFirebaseNativeInstanceIdPtr GetFirebaseNativeInstanceId() const
	{
		return FirebaseNativeInstanceIdPtr;
	}

	/** Convert Native Firebase Error to Unreal Firebase Error */
	static EFirebaseInstanceIdError FirebaseErrorFromNative(const firebase::instance_id::Error& NativeError);
#endif

	/** Returns a token that authorizes an Entity to perform an action on behalf of the application identified by Instance ID. */
	void GetToken(const FOnFirebaseInstanceIdGetTokenCompleteDelegate& Delegate = FOnFirebaseInstanceIdGetTokenCompleteDelegate()) const;

	/** Returns a stable identifier that uniquely identifies the app instance. */
	void GetId(const FOnFirebaseInstanceIdGetIdCompleteDelegate& Delegate = FOnFirebaseInstanceIdGetIdCompleteDelegate()) const;

	/** Revokes access to a scope (action) */
	void DeleteToken(const FOnFirebaseInstanceIdDeleteTokenCompleteDelegate& Delegate = FOnFirebaseInstanceIdDeleteTokenCompleteDelegate()) const;

	/** Delete the ID associated with the app, revoke all tokens and allocate a new ID. */
	void DeleteId(const FOnFirebaseInstanceIdDeleteIdCompleteDelegate& Delegate = FOnFirebaseInstanceIdDeleteIdCompleteDelegate()) const;

private:
	bool bInitialized = false;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	FFirebaseNativeInstanceIdPtr FirebaseNativeInstanceIdPtr;
#endif
};
