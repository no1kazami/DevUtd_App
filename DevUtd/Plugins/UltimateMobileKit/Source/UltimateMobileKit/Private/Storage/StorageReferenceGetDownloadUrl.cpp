// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageReferenceGetDownloadUrl.h"
#include "UltimateMobileKit.h"

FFirebaseStorageReferenceGetDownloadUrl::FFirebaseStorageReferenceGetDownloadUrl(FUltimateMobileKit* InSubsystem, const FOnFirebaseStorageReferenceGetDownloadUrlCompleteDelegate& InDelegate, const UStorageReference* InStorageReference)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, StorageReference(InStorageReference)
{
}

void FFirebaseStorageReferenceGetDownloadUrl::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseStorageReferenceGetDownloadUrl async task..."));

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
					FetchFutureResult = NativeStorageReference->GetDownloadUrl();

					return;
				}
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseStorageReferenceGetDownloadUrl::Tick()
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

		if (FetchFutureResult.error() == 0)
		{
			bWasSuccessful = true;
			DownloadUrl = FString(FetchFutureResult.result()->c_str());
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseStorageReferenceGetDownloadUrl Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseStorageReferenceGetDownloadUrl::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseStorageReferenceGetDownloadUrl async task %s, DownloadUrl: %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"), *DownloadUrl);

	Delegate.ExecuteIfBound(bWasSuccessful, Error, DownloadUrl);
}

void FFirebaseStorageReferenceGetDownloadUrl::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FetchFutureResult.Release();
#endif
}
