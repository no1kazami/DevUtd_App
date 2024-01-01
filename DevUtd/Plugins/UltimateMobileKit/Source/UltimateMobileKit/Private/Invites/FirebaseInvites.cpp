// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Invites/FirebaseInvites.h"
#include "Invites/InvitesInitialize.h"
#include "Invites/InvitesSendInvite.h"
#include "Invites/InvitesConvertInvitation.h"
#include "UltimateMobileKitComponent.h"

FFirebaseInvites::FFirebaseInvites()
{
}

FFirebaseInvites::~FFirebaseInvites()
{
}

void FFirebaseInvites::Init(const FOnFirebaseInvitesInitializeCompleteDelegate& Delegate /*= FOnFirebaseInvitesInitializeCompleteDelegate()*/)
{
	if (IsInitialized())
	{
		Delegate.ExecuteIfBound(true);
		return;
	}

	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		auto QueryTask = new FFirebaseInvitesInitialize(UltimateMobileKit->Get(), Delegate);
		UltimateMobileKit->QueueAsyncTask(QueryTask);

		return;
	}

	Delegate.ExecuteIfBound(false);
}

void FFirebaseInvites::Shutdown()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Invites Shutdown"));

	if(bInitialized)
	{
		if(InvitesListener != nullptr)
		{
			InvitesListener->RemoveFromRoot();
		}
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	firebase::invites::Terminate();
#endif
}

const bool FFirebaseInvites::IsInitialized() const
{
	return bInitialized;
}

void FFirebaseInvites::SetInitialized(const bool Initialized)
{
	bInitialized = Initialized;

	if (bInitialized)
	{
		InvitesListener = NewObject<UFirebaseInvitesListener>();
		InvitesListener->AddToRoot();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
		firebase::invites::SetListener(InvitesListener->GetNativeInvitesListener().Get());
#endif

		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Invites is initialized successfully"));
	}
	else
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Invites is not initialized"));
	}
}

UFirebaseInvitesListener* FFirebaseInvites::GetListener() const
{
	if (IsInitialized() && InvitesListener != nullptr)
	{
		return InvitesListener;
	}
	else
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Invites Listener is null"));

		return nullptr;
	}
}

void FFirebaseInvites::SendInvite(const FFirebaseInvite Invite, const FOnFirebaseInvitesSendInviteCompleteDelegate& Delegate /*= FOnFirebaseInvitesSendInviteCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseInvitesSendInvite(UltimateMobileKit->Get(), Delegate, Invite);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, FFirebaseSendInviteResult());
}

void FFirebaseInvites::ConvertInvitation(const FString& InvitationId, const FOnFirebaseInvitesConvertInvitationCompleteDelegate& Delegate /*= FOnFirebaseInvitesConvertInvitationCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseInvitesConvertInvitation(UltimateMobileKit->Get(), Delegate, InvitationId);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false);
}

void FFirebaseInvites::Fetch() const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	if (IsInitialized())
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Invites Fetch"));

		firebase::invites::Fetch();
	}
#endif
}
