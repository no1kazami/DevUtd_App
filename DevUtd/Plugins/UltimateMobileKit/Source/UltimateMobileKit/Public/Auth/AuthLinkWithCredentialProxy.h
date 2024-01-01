// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "FirebaseCredential.h"
#include "AuthLinkWithCredentialProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthLinkWithCredentialProxySuccess, const EFirebaseAuthError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthLinkWithCredentialProxyFailure, const EFirebaseAuthError&, Error);

/**
* Links the user with the given 3rd party credentials.
* For example, a Facebook login access token, a Twitter token/token-secret pair. Status will be an error if the token is invalid, expired, or otherwise not accepted by the server as well as if the given 3rd party user id is already linked with another user account or if the current user is already linked with another id from the same provider.
*/
UCLASS(MinimalAPI)
class UFirebaseAuthLinkWithCredentialProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthLinkWithCredentialProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthLinkWithCredentialProxyFailure OnFailure;

	/** 
	* Links the user with the given 3rd party credentials.
	* For example, a Facebook login access token, a Twitter token/token-secret pair. Status will be an error if the token is invalid, expired, or otherwise not accepted by the server as well as if the given 3rd party user id is already linked with another user account or if the current user is already linked with another id from the same provider.
	*/
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Link With Credential")
	static UFirebaseAuthLinkWithCredentialProxy* LinkWithCredentialProxy(const UFirebaseCredential* Credential);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error);

private:
	const UFirebaseCredential* Credential;
};
