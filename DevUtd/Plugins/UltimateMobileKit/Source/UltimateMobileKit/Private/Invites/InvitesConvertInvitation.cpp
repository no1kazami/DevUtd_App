// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Invites/InvitesConvertInvitation.h"
#include "UltimateMobileKit.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
#include "firebase/invites.h"
#include "firebase/util.h"
#endif

FFirebaseInvitesConvertInvitation::FFirebaseInvitesConvertInvitation(FUltimateMobileKit* InSubsystem, const FOnFirebaseInvitesConvertInvitationCompleteDelegate& InDelegate, const FString& InInvitationId)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, InvitationId(InInvitationId)
{
}

void FFirebaseInvitesConvertInvitation::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseInvitesConvertInvitation async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInvitesPtr FirebaseInvites = UltimateMobileKit->GetFirebaseInvites();

		if(FirebaseInvites.IsValid() && FirebaseInvites->IsInitialized())
		{
			FetchFutureResult = firebase::invites::ConvertInvitation(TCHAR_TO_UTF8(*InvitationId));

			return;
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseInvitesConvertInvitation::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	if (FetchFutureResult.status() == firebase::kFutureStatusComplete)
	{
		if (FetchFutureResult.error() == 0)
		{
			bWasSuccessful = true;
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseInvitesConvertInvitation Error: %s"), *FString(FetchFutureResult.error_message()));
		}
		bIsComplete = true;
	}

	if (FetchFutureResult.status() == firebase::kFutureStatusInvalid)
	{
		bWasSuccessful = false;
		bIsComplete = true;
	}
#endif
}

void FFirebaseInvitesConvertInvitation::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseInvitesConvertInvitation async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful);
}

void FFirebaseInvitesConvertInvitation::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	FetchFutureResult.Release();
#endif
}
