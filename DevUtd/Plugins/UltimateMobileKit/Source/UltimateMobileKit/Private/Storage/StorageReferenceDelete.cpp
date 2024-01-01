// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageReferenceDelete.h"
#include "UltimateMobileKit.h"

FFirebaseStorageReferenceDelete::FFirebaseStorageReferenceDelete(FUltimateMobileKit* InSubsystem, const FOnFirebaseStorageReferenceDeleteCompleteDelegate& InDelegate, const UStorageReference* InStorageReference)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, StorageReference(InStorageReference)
{
}

void FFirebaseStorageReferenceDelete::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseStorageReferenceDelete async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid() && FirebaseStorage->IsInitialized())
		{
			NativeStorage = FirebaseStorage->GetFirebaseNativeStorage();

			if (NativeStorage.IsValid())
			{
				NativeStorageReference = MakeShareable(new firebase::storage::StorageReference(*(StorageReference->GetNativeStorageReference())));
				if (NativeStorageReference.IsValid() && NativeStorageReference->is_valid())
				{
					FetchFutureResult = NativeStorageReference->Delete();

					return;
				}
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseStorageReferenceDelete::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	if (FetchFutureResult.status() == firebase::kFutureStatusComplete)
	{
		Error = FFirebaseStorage::FirebaseErrorFromNative(static_cast<firebase::storage::Error>(FetchFutureResult.error()));

		if (FetchFutureResult.error() == firebase::storage::kErrorNone)
		{
			bWasSuccessful = true;
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseStorageReferenceDelete Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseStorageReferenceDelete::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseStorageReferenceDelete async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, Error);
}

void FFirebaseStorageReferenceDelete::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FetchFutureResult.Release();
#endif
}
