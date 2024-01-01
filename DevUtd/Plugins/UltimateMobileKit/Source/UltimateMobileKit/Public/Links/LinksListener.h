// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "Delegates/FirebaseLinksDelegates.h"
#include "LinksListener.generated.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
#include "firebase/dynamic_links.h"
#endif


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseLinksListenerOnDynamicLinkReceived, const FFirebaseDynamicLink, DynamicLink);


class FFirebaseLinksListener
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	: public firebase::dynamic_links::Listener
#endif
{
public:
	FFirebaseLinksListener(FFirebaseLinksListenerOnDynamicLinkReceived* InOnDynamicLinkReceivedEvent);
	virtual ~FFirebaseLinksListener();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	/** Called on the client when a dynamic link arrives. */
	virtual void OnDynamicLinkReceived(const firebase::dynamic_links::DynamicLink *dynamic_link) override;
#endif

private:
	FFirebaseLinksListenerOnDynamicLinkReceived* OnDynamicLinkReceivedEvent;
};


typedef TSharedPtr<FFirebaseLinksListener, ESPMode::ThreadSafe> FFirebaseNativeLinksListenerPtr;

/** Class used to receive Invites and Dynamic Links. */
UCLASS()
class ULTIMATEMOBILEKIT_API UFirebaseLinksListener : public UObject
{
public:
	GENERATED_UCLASS_BODY()

	virtual ~UFirebaseLinksListener();

	/** Called on the client when a dynamic link arrives. */
	UPROPERTY(BlueprintAssignable)
	FFirebaseLinksListenerOnDynamicLinkReceived OnDynamicLinkReceivedEvent;

	/** Get Native Links Listener */
	FFirebaseNativeLinksListenerPtr GetNativeLinksListener();

private:
	FFirebaseNativeLinksListenerPtr NativeLinksListener;
};
