// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthGetUserTokenProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFirebaseGetUserTokenSuccess, const EFirebaseAuthError&, Error, const FString&, Token);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseGetUserTokenFailure, const EFirebaseAuthError&, Error);

/** The Java Web Token (JWT) that can be used to identify the user to the backend */
UCLASS(MinimalAPI)
class UFirebaseAuthGetUserTokenProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseGetUserTokenSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseGetUserTokenFailure OnFailure;

	/** The Java Web Token (JWT) that can be used to identify the user to the backend */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Get User Token")
	static UFirebaseAuthGetUserTokenProxy* GetUserToken(const bool ForceRefresh = false);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error, const FString& Token);

private:
	bool ForceRefresh;
};
