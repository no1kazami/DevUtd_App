// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseAuthDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
#include "firebase/future.h"
#include "firebase/auth.h"
#endif

class FUltimateMobileKit;

/**
* Links the user with the given 3rd party credentials.
* For example, a Facebook login access token, a Twitter token/token-secret pair. Status will be an error if the token is invalid, expired, or otherwise not accepted by the server as well as if the given 3rd party user id is already linked with another user account or if the current user is already linked with another id from the same provider.
*/
class FFirebaseAuthLinkWithCredential : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseAuthLinkWithCredential(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthLinkWithCredentialCompleteDelegate& InDelegate, const UFirebaseCredential* InCredential);

	virtual FString ToString() const override { return TEXT("FirebaseAuthLinkWithCredential"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseAuthLinkWithCredentialCompleteDelegate Delegate;
	EFirebaseAuthError Error;
	const UFirebaseCredential* Credential;

#if WITH_ULTIMATEMOBILEKIT&& WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FFirebaseNativeAuthPtr NativeAuth;
	firebase::Future<firebase::auth::User*> FetchFutureResult;
#endif
};
