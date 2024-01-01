// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseAnalyticsDelegates.h"
#include "AnalyticsGetAnalyticsInstanceIdProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseAnalyticsGetAnalyticsInstanceIdSuccess, const FString&, AnalyticsInstanceId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFirebaseAnalyticsGetAnalyticsInstanceIdFailure);

/** Get the instance ID from the analytics service. */
UCLASS(MinimalAPI)
class UFirebaseAnalyticsGetAnalyticsInstanceIdProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseAnalyticsGetAnalyticsInstanceIdSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFirebaseAnalyticsGetAnalyticsInstanceIdFailure OnFailure;

	/** Get the instance ID from the analytics service. */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Analytics", DisplayName = "Firebase Analytics Get Analytics Instance Id")
	static UFirebaseAnalyticsGetAnalyticsInstanceIdProxy* GetAnalyticsInstanceId();

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const FString& AnalyticsInstanceId);
};
