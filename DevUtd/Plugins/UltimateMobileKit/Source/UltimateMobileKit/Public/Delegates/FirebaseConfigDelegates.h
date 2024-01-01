// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "FirebaseConfigDelegates.generated.h"

/** Called when Firebase Config module is initialized */
DECLARE_DELEGATE_OneParam(FOnFirebaseConfigInitializeCompleteDelegate, const bool);

/** Called when Firebase fetching config is completed */
DECLARE_DELEGATE_OneParam(FOnFirebaseConfigFetchCompleteDelegate, const bool);

/** Describes the most recent fetch failure */
UENUM(BlueprintType)
enum class EFetchFailureReason : uint8
{
    /** The most recent fetch failed for an unknown reason */
	FetchFailureReasonError,
    
    /** The fetch has not yet failed */
	FetchFailureReasonInvalid,
    
    /** The most recent fetch failed because it was throttled by the server (You are sending too many fetch requests in too short a time) */
	FetchFailureReasonThrottled
};

/** Describes the most recent fetch request status */
UENUM(BlueprintType)
enum class ELastFetchStatus : uint8
{
    /** The most recent fetch request failed */
	LastFetchStatusFailure,
    
    /** The most recent fetch is still in progress */
	LastFetchStatusPending,
    
    /** The most recent fetch was a success, and its data is ready to be applied, if you have not already done so */
	LastFetchStatusSuccess
};

/** Describes the state of the most recent Config Fetch call */
USTRUCT(BlueprintType)
struct FRemoteConfigInfo
{
	GENERATED_USTRUCT_BODY()

    /** The time (in seconds since the epoch) that the last fetch operation completed */
	UPROPERTY(BlueprintReadOnly, Category = "Ultimate Mobile Kit|Remote Config")
	FString FetchTime;

    /** The time (in seconds since the epoch) when the refreshing of Remote Config data is throttled */
	UPROPERTY(BlueprintReadOnly, Category = "Ultimate Mobile Kit|Remote Config")
	FString ThrottledEndTime;

    /** The reason the most recent fetch failed */
	UPROPERTY(BlueprintReadOnly, Category = "Ultimate Mobile Kit|Remote Config")
	EFetchFailureReason FetchFailureReason;

    /** The status of the last fetch request */
	UPROPERTY(BlueprintReadOnly, Category = "Ultimate Mobile Kit|Remote Config")
	ELastFetchStatus LastFetchStatus;

	FRemoteConfigInfo()
	{
		FetchTime = FString("0");
		ThrottledEndTime = FString("0");
		FetchFailureReason = EFetchFailureReason::FetchFailureReasonInvalid;
		LastFetchStatus = ELastFetchStatus::LastFetchStatusFailure;
	}
};
