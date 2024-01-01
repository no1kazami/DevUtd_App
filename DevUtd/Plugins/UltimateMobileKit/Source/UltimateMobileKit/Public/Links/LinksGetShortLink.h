// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineAsyncTaskManager.h"
#include "Delegates/FirebaseLinksDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
#include "firebase/future.h"
#include "firebase/dynamic_links.h"
#endif

class FUltimateMobileKit;

/** Creates a shortened Dynamic Link from the given parameters. */
class FFirebaseLinksGetShortLink : public FOnlineAsyncTaskBasic<FUltimateMobileKit>
{
public:
	FFirebaseLinksGetShortLink(FUltimateMobileKit* InSubsystem, const FOnFirebaseLinksGetShortLinkCompleteDelegate& InDelegate, const FFirebaseDynamicLinkComponents& InDynamicLinkComponents);
	FFirebaseLinksGetShortLink(FUltimateMobileKit* InSubsystem, const FOnFirebaseLinksGetShortLinkCompleteDelegate& InDelegate, const FFirebaseDynamicLinkComponents& InDynamicLinkComponents, const FFirebaseDynamicLinkOptions& InDynamicLinkOptions);
	FFirebaseLinksGetShortLink(FUltimateMobileKit* InSubsystem, const FOnFirebaseLinksGetShortLinkCompleteDelegate& InDelegate, const FString& InLongDynamicLink);
	FFirebaseLinksGetShortLink(FUltimateMobileKit* InSubsystem, const FOnFirebaseLinksGetShortLinkCompleteDelegate& InDelegate, const FString& InLongDynamicLink, const FFirebaseDynamicLinkOptions& InDynamicLinkOptions);

	virtual FString ToString() const override { return TEXT("FirebaseLinksGetShortLink"); }
	virtual void Finalize() override;
	virtual void TriggerDelegates() override;
	virtual void Tick() override;

private:
	bool bInit = false;
	void Start_OnTaskThread();
	const FOnFirebaseLinksGetShortLinkCompleteDelegate Delegate;
	FFirebaseDynamicLinkComponents DynamicLinkComponents;
	FFirebaseDynamicLinkOptions DynamicLinkOptions;
	FString LongDynamicLink;
	FFirebaseGeneratedDynamicLink GeneratedDynamicLink;

	bool bUseDynamicLinkComponents = false;
	bool bUseDynamicLinkOptions = false;
	bool bUseLongDynamicLink = false;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	firebase::Future<firebase::dynamic_links::GeneratedDynamicLink> FetchFutureResult;
#endif
};
