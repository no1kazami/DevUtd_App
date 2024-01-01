// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/StorageController.h"

UStorageController::UStorageController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	NativeStorageController = MakeShareable(new firebase::storage::Controller());
#endif
}

bool UStorageController::Cancel()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	if (NativeStorageController.IsValid() && NativeStorageController->is_valid())
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Cancel task in Storage Controller"));

		return NativeStorageController->Cancel();
	}
#endif

	return false;
}

bool UStorageController::Pause()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	if (NativeStorageController.IsValid() && NativeStorageController->is_valid())
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Pause task in Storage Controller"));

		return NativeStorageController->Pause();
	}
#endif

	return false;
}

bool UStorageController::Resume()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	if (NativeStorageController.IsValid() && NativeStorageController->is_valid())
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Resume task in Storage Controller"));

		return NativeStorageController->Resume();
	}
#endif

	return false;
}

bool UStorageController::IsPaused()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	if (NativeStorageController.IsValid() && NativeStorageController.Get()->is_valid())
	{
		bool bIsPaused = NativeStorageController->is_paused();

		UE_LOG(LogUltimateMobileKit, Display, TEXT("Task in Storage Controller is %s"), bIsPaused ? TEXT("paused") : TEXT("is not paused"));

		return bIsPaused;
	}
#endif

	return false;
}

bool UStorageController::IsValid()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	if (NativeStorageController.IsValid())
	{
		bool bIsValid = NativeStorageController->is_valid();

		UE_LOG(LogUltimateMobileKit, Display, TEXT("Task in Storage Controller is %s"), bIsValid ? TEXT("valid") : TEXT("is not valid"));

		return bIsValid;
	}
#endif

	return false;
}

float UStorageController::GetProgress()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	if (NativeStorageController.IsValid() && NativeStorageController->is_valid())
	{
		double BytesTransferred = static_cast<double>(NativeStorageController->bytes_transferred());
		double TotalByteCount = static_cast<double>(NativeStorageController->total_byte_count());

		if (TotalByteCount != 0)
		{
			float Progress = (float) (BytesTransferred / TotalByteCount);

			UE_LOG(LogUltimateMobileKit, Display, TEXT("Progress of task in Storage Controller is %s"), *FString::SanitizeFloat(Progress));

			return Progress;
		}
		else
		{
			return 0;
		}
	}
#endif

	return 0;
}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
FFirebaseNativeStorageControllerPtr UStorageController::GetNativeStorageController()
{
	return NativeStorageController;
}
#endif
