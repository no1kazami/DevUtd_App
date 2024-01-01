// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Delegates/FirebaseLinksDelegates.h"
#include "Links/LinksListener.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
#include "firebase/dynamic_links.h"
#include "firebase/dynamic_links/components.h"
#endif

/** Firebase Links is for generating and receiving links, whether or not the app is already installed. */
class ULTIMATEMOBILEKIT_API FFirebaseLinks
{
public:
	FFirebaseLinks();
	virtual ~FFirebaseLinks();

	/** Initialize the Firebase Dynamic Links API  */
	void Init(UFirebaseLinksListener* Listener, const FOnFirebaseLinksInitializeCompleteDelegate& Delegate = FOnFirebaseLinksInitializeCompleteDelegate());

	/** Shutdown the Firebase Dynamic Links API  */
	void Shutdown();

	/** Check if Firebase Dynamic Links is initialized */
	const bool IsInitialized() const;

	/** Set Firebase Dynamic Links initialization state */
	void SetInitialized(bool Initialized);

	/** Create Firebase Links Listener */
	UFirebaseLinksListener* CreateListener() const;

	/** Fetch any pending dynamic links. */
	void Fetch() const;

	/** Creates a long Dynamic Link from the given parameters. */
	const FFirebaseGeneratedDynamicLink GetLongLink(const FFirebaseDynamicLinkComponents& DynamicLinkComponents) const;

	/** Creates a shortened Dynamic Link from the given parameters. */
	void GetShortLink(FFirebaseDynamicLinkComponents DynamicLinkComponents, const FOnFirebaseLinksGetShortLinkCompleteDelegate& Delegate = FOnFirebaseLinksGetShortLinkCompleteDelegate()) const;

	/** Creates a shortened Dynamic Link from the given parameters. */
	void GetShortLink(FFirebaseDynamicLinkComponents DynamicLinkComponents, FFirebaseDynamicLinkOptions DynamicLinkOptions, const FOnFirebaseLinksGetShortLinkCompleteDelegate& Delegate = FOnFirebaseLinksGetShortLinkCompleteDelegate()) const;

	/** Creates a shortened Dynamic Link from the given parameters. */
	void GetShortLink(FString LongDynamicLink, const FOnFirebaseLinksGetShortLinkCompleteDelegate& Delegate = FOnFirebaseLinksGetShortLinkCompleteDelegate()) const;

	/** Creates a shortened Dynamic Link from the given parameters. */
	void GetShortLink(FString LongDynamicLink, FFirebaseDynamicLinkOptions DynamicLinkOptions, const FOnFirebaseLinksGetShortLinkCompleteDelegate& Delegate = FOnFirebaseLinksGetShortLinkCompleteDelegate()) const;

private:
	bool bInitialized = false;
	
	UPROPERTY()
	UFirebaseLinksListener* LinksListener;
};
