// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthUpdateUserProfileProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthUpdateProfileProxySuccess, const EFirebaseAuthError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthUpdateProfileProxyFailure, const EFirebaseAuthError&, Error);

/** Updates a subset of user profile information */
UCLASS(MinimalAPI)
class UFirebaseAuthUpdateUserProfileProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthUpdateProfileProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthUpdateProfileProxyFailure OnFailure;

	/** Updates a subset of user profile information */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Update User Profile")
	static UFirebaseAuthUpdateUserProfileProxy* UpdateUserProfile(const FFirebaseUserProfile UserProfile);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error);

private:
	FFirebaseUserProfile UserProfile;
};
