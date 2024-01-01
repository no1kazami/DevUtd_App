// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Links/LinksListener.h"

FFirebaseLinksListener::FFirebaseLinksListener(FFirebaseLinksListenerOnDynamicLinkReceived* InOnDynamicLinkReceivedEvent)
{
	OnDynamicLinkReceivedEvent = InOnDynamicLinkReceivedEvent;
}

FFirebaseLinksListener::~FFirebaseLinksListener()
{
}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
void FFirebaseLinksListener::OnDynamicLinkReceived(const firebase::dynamic_links::DynamicLink *dynamic_link)
{
	FFirebaseDynamicLink DynamicLink;

	if(dynamic_link != nullptr)
	{
		DynamicLink.Url = FString(dynamic_link->url.c_str());

		if(dynamic_link->match_strength == firebase::dynamic_links::LinkMatchStrength::kLinkMatchStrengthNoMatch)
		{
			DynamicLink.MatchStrength = EFirebaseLinksLinkMatchStrength::NoMatch;
		}
		else if (dynamic_link->match_strength == firebase::dynamic_links::LinkMatchStrength::kLinkMatchStrengthPerfectMatch)
		{
			DynamicLink.MatchStrength = EFirebaseLinksLinkMatchStrength::PerfectMatch;
		}
		else if (dynamic_link->match_strength == firebase::dynamic_links::LinkMatchStrength::kLinkMatchStrengthStrongMatch)
		{
			DynamicLink.MatchStrength = EFirebaseLinksLinkMatchStrength::StrongMatch;
		}
		else if (dynamic_link->match_strength == firebase::dynamic_links::LinkMatchStrength::kLinkMatchStrengthWeakMatch)
		{
			DynamicLink.MatchStrength = EFirebaseLinksLinkMatchStrength::WeakMatch;
		}
		else
		{
			DynamicLink.MatchStrength = EFirebaseLinksLinkMatchStrength::NoMatch;
		}

		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase On Dynamic Link Received: %s"), *DynamicLink.Url);
	}
	else
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase On Dynamic Link Received: can't process URL"));
	}


	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_OnDynamicLinkReceived"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_OnDynamicLinkReceived, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
			OnDynamicLinkReceivedEvent->Broadcast(DynamicLink);
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_OnDynamicLinkReceived),
		nullptr,
		ENamedThreads::GameThread
	);
}
#endif

UFirebaseLinksListener::UFirebaseLinksListener(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NativeLinksListener = MakeShareable(new FFirebaseLinksListener(&OnDynamicLinkReceivedEvent));
}

UFirebaseLinksListener::~UFirebaseLinksListener()
{
	NativeLinksListener.Reset();
}

FFirebaseNativeLinksListenerPtr UFirebaseLinksListener::GetNativeLinksListener()
{
	return NativeLinksListener;
}
