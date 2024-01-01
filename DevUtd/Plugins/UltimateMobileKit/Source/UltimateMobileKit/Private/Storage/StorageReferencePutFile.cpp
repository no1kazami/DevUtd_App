// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageReferencePutFile.h"
#include "UltimateMobileKit.h"

FFirebaseStorageReferencePutFile::FFirebaseStorageReferencePutFile(FUltimateMobileKit* InSubsystem, const FOnFirebaseStorageReferencePutFileCompleteDelegate& InDelegate, const FOnFirebaseStorageReferencePutFileStartCompleteDelegate& InStartDelegate, const UStorageReference* InStorageReference, const FString& InPathFile)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, StartDelegate(InStartDelegate)
	, StorageReference(InStorageReference)
	, PathFile(InPathFile)
{
}

void FFirebaseStorageReferencePutFile::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseStorageReferencePutFile async task..."));

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
					StorageListener = NewObject<UFirebaseStorageListener>();
					StorageListener->AddToRoot();
					StorageController = NewObject<UStorageController>();
					StorageController->AddToRoot();
					FFirebaseNativeStorageControllerPtr NativeStorageController = StorageController->GetNativeStorageController();

					if (NativeStorageController.IsValid())
					{
						FString FinalPathFile = PathFile;

						if(!FinalPathFile.StartsWith("file://"))
						{
							FinalPathFile = FString("file://") + FinalPathFile;
						}

						PathFileShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*FinalPathFile)));
						FetchFutureResult = NativeStorageReference->PutFile(PathFileShared->c_str(), StorageListener->GetNativeStorageListener().Get(), NativeStorageController.Get());
						StartDelegate.ExecuteIfBound(StorageListener, StorageController);

						return;
					}
				}
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseStorageReferencePutFile::Tick()
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
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseStorageReferencePutFile Error: %s"), *FString(FetchFutureResult.error_message()));
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

void FFirebaseStorageReferencePutFile::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseStorageReferencePutFile async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, Error);
}

void FFirebaseStorageReferencePutFile::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FetchFutureResult.Release();

	if (StorageController)
	{
		StorageController->RemoveFromRoot();
	}

	if (StorageListener)
	{
		StorageListener->RemoveFromRoot();
	}
#endif
}
