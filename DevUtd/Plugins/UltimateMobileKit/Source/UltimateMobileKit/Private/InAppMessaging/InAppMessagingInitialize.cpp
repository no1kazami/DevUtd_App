// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "InAppMessaging/InAppMessagingInitialize.h"
#include "UltimateMobileKit.h"

FFirebaseInAppMessagingInitialize::FFirebaseInAppMessagingInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseInAppMessagingInitializeCompleteDelegate& InDelegate)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
{
}

void FFirebaseInAppMessagingInitialize::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseInAppMessagingInitialize async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INAPPMESSAGING
	bWasSuccessful = true;
	bIsComplete = true;
	return;
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseInAppMessagingInitialize::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}
}

void FFirebaseInAppMessagingInitialize::TriggerDelegates()
{
	Delegate.ExecuteIfBound(bWasSuccessful);
}

void FFirebaseInAppMessagingInitialize::Finalize()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseInAppMessagingInitialize async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INAPPMESSAGING
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInAppMessagingPtr FirebaseInAppMessaging = UltimateMobileKit->GetFirebaseInAppMessaging();

		if (FirebaseInAppMessaging.IsValid())
		{
			if (bWasSuccessful)
			{
				FirebaseInAppMessaging->SetInitialized(true);
			}
			else
			{
				FirebaseInAppMessaging->SetInitialized(false);
			}
		}
	}
#endif
}
