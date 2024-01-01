// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Delegates/FirebaseLinksDelegates.h"
#include "LinksGetShortLinkProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseGetShortLinkSuccess, const FFirebaseGeneratedDynamicLink, GeneratedDynamicLink);

/** Creates a shortened Dynamic Link from the given parameters. */
UCLASS(MinimalAPI)
class UFirebaseLinksGetShortLinkProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FFirebaseGetShortLinkSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	/** Creates a shortened Dynamic Link from the given parameters. */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|Dynamic Links", DisplayName = "Firebase Dynamic Links Get Short Link")
	static UFirebaseLinksGetShortLinkProxy* GetShortLink(const FFirebaseDynamicLinkComponents DynamicLinkComponents, const FFirebaseDynamicLinkOptions DynamicLinkOptions, const FString& LongDynamicLink);

	virtual void Activate() override;

private:
	void OnQueryCompleted(bool bSuccess, const FFirebaseGeneratedDynamicLink GeneratedDynamicLink);

private:
	FFirebaseDynamicLinkComponents DynamicLinkComponents;
	FFirebaseDynamicLinkOptions DynamicLinkOptions;
	FString LongDynamicLink;
};
