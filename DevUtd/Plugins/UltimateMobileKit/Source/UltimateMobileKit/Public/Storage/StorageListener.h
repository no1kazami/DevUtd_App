// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "StorageListener.generated.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
#include "firebase/storage/listener.h"
#endif

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseStorageListenerOnProgress, const float, Progress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFirebaseStorageListenerOnPaused);

class FFirebaseStorageListener
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	: public firebase::storage::Listener
#endif
{
public:
	FFirebaseStorageListener(FFirebaseStorageListenerOnProgress* InOnProgressEvent, FFirebaseStorageListenerOnPaused* InOnPausedEvent);
	virtual ~FFirebaseStorageListener();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	/** Called when there has been progress event */
	virtual void OnProgress(firebase::storage::Controller* controller) override;

	/** Called when the operation was paused */
	virtual void OnPaused(firebase::storage::Controller* controller) override;
#endif

private:
	FFirebaseStorageListenerOnProgress* OnProgressEvent;
	FFirebaseStorageListenerOnPaused* OnPausedEvent;
};


typedef TSharedPtr<FFirebaseStorageListener, ESPMode::ThreadSafe> FFirebaseNativeStorageListenerPtr;

/** Class used to receive pause and progress events on a running read or write operation. */
UCLASS()
class ULTIMATEMOBILEKIT_API UFirebaseStorageListener : public UObject
{
public:
	GENERATED_UCLASS_BODY()

	virtual ~UFirebaseStorageListener();

	/** Called when there has been progress event */
	UPROPERTY(BlueprintAssignable)
	FFirebaseStorageListenerOnProgress OnProgressEvent;

	/** Called when the operation was paused */
	UPROPERTY(BlueprintAssignable)
	FFirebaseStorageListenerOnPaused OnPausedEvent;

	/** Get Native Storage Listener */
	FFirebaseNativeStorageListenerPtr GetNativeStorageListener();

private:
	FFirebaseNativeStorageListenerPtr NativeStorageListener;
};
