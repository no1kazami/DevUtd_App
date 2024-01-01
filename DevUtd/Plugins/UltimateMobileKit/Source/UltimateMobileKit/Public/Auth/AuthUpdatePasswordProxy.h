// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthUpdatePasswordProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthUpdatePasswordProxySuccess, const EFirebaseAuthError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthUpdatePasswordProxyFailure, const EFirebaseAuthError&, Error);

/*
 * Attempts to change the password for the current user.
 * For an account linked to an Identity Provider (IDP) with no password, this will result in the account becoming an email/password-based account while maintaining the IDP link. May fail if the password is invalid, if there is a conflicting email/password-based account, or if the token has expired. To retrieve fresh tokens, call Reauthenticate.
*/
UCLASS(MinimalAPI)
class UFirebaseAuthUpdatePasswordProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthUpdatePasswordProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthUpdatePasswordProxyFailure OnFailure;

	/*
	* Attempts to change the password for the current user.
	* For an account linked to an Identity Provider (IDP) with no password, this will result in the account becoming an email/password-based account while maintaining the IDP link. May fail if the password is invalid, if there is a conflicting email/password-based account, or if the token has expired. To retrieve fresh tokens, call Reauthenticate.
	*/
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Update Password")
	static UFirebaseAuthUpdatePasswordProxy* UpdatePassword(const FString& Password);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error);

private:
	FString Password;
};
