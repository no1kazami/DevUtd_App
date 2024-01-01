// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthSignInAnonymousProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthSignInAnonymousProxySuccess, const EFirebaseAuthError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthSignInAnonymousProxyFailure, const EFirebaseAuthError&, Error);

/** 
* Asynchronously creates and becomes an anonymous user.
* If there is already an anonymous user signed in, that user will be returned instead. If there is any other existing user, that user will be signed out.
*/
UCLASS(MinimalAPI)
class UFirebaseAuthSignInAnonymousProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthSignInAnonymousProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthSignInAnonymousProxyFailure OnFailure;

	/**
	 * Asynchronously creates and becomes an anonymous user.
	 * If there is already an anonymous user signed in, that user will be returned instead. If there is any other existing user, that user will be signed out.
	*/
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Sign In Anonymously")
	static UFirebaseAuthSignInAnonymousProxy* SignInAnonymously();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error);
};
