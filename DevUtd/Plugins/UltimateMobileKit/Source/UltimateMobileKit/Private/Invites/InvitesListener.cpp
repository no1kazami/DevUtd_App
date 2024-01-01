// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Invites/InvitesListener.h"

FFirebaseInvitesListener::FFirebaseInvitesListener(FFirebaseInvitesListenerOnErrorReceived* InOnErrorReceivedEvent, FFirebaseInvitesListenerOnInviteNotReceived* InOnInviteNotReceivedEvent, FFirebaseInvitesListenerOnInviteReceived* InOnInviteReceivedEvent)
{
	OnErrorReceivedEvent = InOnErrorReceivedEvent;
	OnInviteNotReceivedEvent = InOnInviteNotReceivedEvent;
	OnInviteReceivedEvent = InOnInviteReceivedEvent;
}

FFirebaseInvitesListener::~FFirebaseInvitesListener()
{
}


#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
void FFirebaseInvitesListener::OnErrorReceived(int error_code, const char *error_message)
{	
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_OnErrorReceivedEvent"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_OnErrorReceivedEvent, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
			OnErrorReceivedEvent->Broadcast((int32)error_code, FString(error_message));
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_OnErrorReceivedEvent),
		nullptr,
		ENamedThreads::GameThread
	);
}

void FFirebaseInvitesListener::OnInviteNotReceived()
{
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_OnInviteNotReceivedEvent"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_OnInviteNotReceivedEvent, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
			OnInviteNotReceivedEvent->Broadcast();
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_OnInviteNotReceivedEvent),
		nullptr,
		ENamedThreads::GameThread
	);
}

void FFirebaseInvitesListener::OnInviteReceived(const char *invitation_id, const char *dynamic_link, firebase::invites::LinkMatchStrength match_strength)
{
	FString InvitationId = FString("");
	FString DynamicLink = FString("");
	EFirebaseInvitesLinkMatchStrength MatchStrength = EFirebaseInvitesLinkMatchStrength::NoMatch;

	if (invitation_id != nullptr)
	{
		InvitationId = FString(invitation_id);
	}

	if (dynamic_link != nullptr)
	{
		DynamicLink = FString(dynamic_link);

		if (match_strength == firebase::invites::LinkMatchStrength::kLinkMatchStrengthNoMatch)
		{
			MatchStrength = EFirebaseInvitesLinkMatchStrength::NoMatch;
		}
		else if (match_strength == firebase::invites::LinkMatchStrength::kLinkMatchStrengthPerfectMatch)
		{
			MatchStrength = EFirebaseInvitesLinkMatchStrength::PerfectMatch;
		}
		else if (match_strength == firebase::invites::LinkMatchStrength::kLinkMatchStrengthStrongMatch)
		{
			MatchStrength = EFirebaseInvitesLinkMatchStrength::StrongMatch;
		}
		else if (match_strength == firebase::invites::LinkMatchStrength::kLinkMatchStrengthWeakMatch)
		{
			MatchStrength = EFirebaseInvitesLinkMatchStrength::WeakMatch;
		}
		else
		{
			MatchStrength = EFirebaseInvitesLinkMatchStrength::NoMatch;
		}
	}

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_OnInviteReceivedEvent"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_OnInviteReceivedEvent, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
			OnInviteReceivedEvent->Broadcast(InvitationId, DynamicLink, MatchStrength);
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_OnInviteReceivedEvent),
		nullptr,
		ENamedThreads::GameThread
	);
}

#endif


UFirebaseInvitesListener::UFirebaseInvitesListener(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NativeInvitesListener = MakeShareable(new FFirebaseInvitesListener(&OnErrorReceivedEvent, &OnInviteNotReceivedEvent, &OnInviteReceivedEvent));
}

UFirebaseInvitesListener::~UFirebaseInvitesListener()
{
	NativeInvitesListener.Reset();
}

FFirebaseNativeInvitesListenerPtr UFirebaseInvitesListener::GetNativeInvitesListener()
{
	return NativeInvitesListener;
}
