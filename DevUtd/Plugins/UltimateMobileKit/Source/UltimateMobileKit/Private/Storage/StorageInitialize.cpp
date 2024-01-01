// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageInitialize.h"
#include "UltimateMobileKit.h"

FFirebaseStorageInitialize::FFirebaseStorageInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseStorageInitializeCompleteDelegate& InDelegate)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
{
}

void FFirebaseStorageInitialize::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseStorageInitialize async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAppPtr FirebaseApp = UltimateMobileKit->GetFirebaseApp();

		if (FirebaseApp.IsValid() && FirebaseApp->IsInitialized())
		{
			FFirebaseNativeAppPtr NativeApp = FirebaseApp->GetFirebaseNativeApp();

			if (NativeApp.IsValid())
			{
				Initializer.Initialize(NativeApp.Get(), nullptr, [](firebase::App* app, void*)
				{
					firebase::InitResult init_result;
					firebase::storage::Storage::GetInstance(app, &init_result);
					return init_result;
				});

				return;
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseStorageInitialize::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	firebase::Future<void> LastResult = Initializer.InitializeLastResult();
	if (LastResult.status() == 0)
	{
		Error = FFirebaseStorage::FirebaseErrorFromNative(static_cast<firebase::storage::Error>(LastResult.error()));

		if (LastResult.error() == 0)
		{
			bWasSuccessful = true;
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseStorageInitialize Error: %s"), *FString(LastResult.error_message()));
		}
		bIsComplete = true;
	}

	if (Initializer.InitializeLastResult().status() == firebase::kFutureStatusInvalid)
	{
		bWasSuccessful = false;
		bIsComplete = true;
	}
	LastResult.Release();
#endif
}

void FFirebaseStorageInitialize::TriggerDelegates()
{
	Delegate.ExecuteIfBound(bWasSuccessful, Error);
}

void FFirebaseStorageInitialize::Finalize()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseStorageInitialize async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseStoragePtr FirebaseStorage = UltimateMobileKit->GetFirebaseStorage();

		if (FirebaseStorage.IsValid())
		{
			if (bWasSuccessful && FirebaseStorage->RegisterService())
			{
				// Settings
				const UUltimateMobileKitSettings* DefaultSettings = GetDefault<UUltimateMobileKitSettings>();

				FirebaseStorage->GetFirebaseNativeStorage()->set_max_download_retry_time(DefaultSettings->MaxDownloadRetryTime);
				FirebaseStorage->GetFirebaseNativeStorage()->set_max_operation_retry_time(DefaultSettings->MaxOperationRetryTime);
				FirebaseStorage->GetFirebaseNativeStorage()->set_max_upload_retry_time(DefaultSettings->MaxUploadRetryTime);

				UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Storage default settings. Max download retry time: %s, max operation retry time: %s, max upload retry time: %s"), *FString::SanitizeFloat(DefaultSettings->MaxDownloadRetryTime), *FString::SanitizeFloat(DefaultSettings->MaxOperationRetryTime), *FString::SanitizeFloat(DefaultSettings->MaxUploadRetryTime));

				FirebaseStorage->SetInitialized(true);
			}
			else
			{
				FirebaseStorage->SetInitialized(false);
			}
		}
	}
#endif
}
