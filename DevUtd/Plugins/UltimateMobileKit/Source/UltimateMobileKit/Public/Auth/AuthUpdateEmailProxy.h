// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAuthDelegates.h"
#include "AuthUpdateEmailProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthUpdateEmailProxySuccess, const EFirebaseAuthError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAuthUpdateEmailProxyFailure, const EFirebaseAuthError&, Error);

/** Sets the email address for the user */
UCLASS(MinimalAPI)
class UFirebaseAuthUpdateEmailProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthUpdateEmailProxySuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAuthUpdateEmailProxyFailure OnFailure;

	/** Sets the email address for the user */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Authentication", DisplayName = "Firebase Authentication Update Email")
	static UFirebaseAuthUpdateEmailProxy* UpdateEmail(const FString& Email);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const EFirebaseAuthError& Error);

private:
	FString Email;
};
