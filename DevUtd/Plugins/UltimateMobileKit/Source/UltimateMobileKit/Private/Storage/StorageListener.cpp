// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageListener.h"

FFirebaseStorageListener::FFirebaseStorageListener(FFirebaseStorageListenerOnProgress* InOnProgressEvent, FFirebaseStorageListenerOnPaused* InOnPausedEvent)
{
	OnProgressEvent = InOnProgressEvent;
	OnPausedEvent = InOnPausedEvent;
}

FFirebaseStorageListener::~FFirebaseStorageListener()
{
}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
void FFirebaseStorageListener::OnProgress(firebase::storage::Controller* controller)
{
	if (controller != nullptr && controller->is_valid())
	{
		double BytesTransferred = static_cast<double>(controller->bytes_transferred());
		double TotalByteCount = static_cast<double>(controller->total_byte_count());

		DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_OnProgressEvent"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_OnProgressEvent, STATGROUP_TaskGraphTasks);

		FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
			FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
				if (TotalByteCount != 0)
				{
					OnProgressEvent->Broadcast((float)(BytesTransferred / TotalByteCount));
				}
				else
				{
					OnProgressEvent->Broadcast(0);
				}
			}),
			GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_OnProgressEvent),
			nullptr,
			ENamedThreads::GameThread
		);
	}
}

void FFirebaseStorageListener::OnPaused(firebase::storage::Controller* controller)
{
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_OnPausedEvent"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_OnPausedEvent, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
			OnPausedEvent->Broadcast();
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_OnPausedEvent),
		nullptr,
		ENamedThreads::GameThread
	);
}
#endif

UFirebaseStorageListener::UFirebaseStorageListener(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NativeStorageListener = MakeShareable(new FFirebaseStorageListener(&OnProgressEvent, &OnPausedEvent));
}

UFirebaseStorageListener::~UFirebaseStorageListener()
{
	NativeStorageListener.Reset();
}

FFirebaseNativeStorageListenerPtr UFirebaseStorageListener::GetNativeStorageListener()
{
	return NativeStorageListener;
}
