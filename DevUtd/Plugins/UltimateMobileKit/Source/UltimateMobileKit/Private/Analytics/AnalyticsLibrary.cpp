// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Analytics/AnalyticsLibrary.h"
#include "UltimateMobileKit.h"

UUltimateMobileKitAnalytics::UUltimateMobileKitAnalytics(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const bool UUltimateMobileKitAnalytics::IsFirebaseAnalyticsInitialized()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAnalyticsPtr FirebaseAnalytics = UltimateMobileKit->GetFirebaseAnalytics();

		if (FirebaseAnalytics.IsValid())
		{
			return FirebaseAnalytics->IsInitialized();
		}
	}

	return false;
}

void UUltimateMobileKitAnalytics::LogEvent(const FString& Name, const TArray<UFirebaseVariant*> Parameters)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAnalyticsPtr FirebaseAnalytics = UltimateMobileKit->GetFirebaseAnalytics();

		if (FirebaseAnalytics.IsValid())
		{
			FirebaseAnalytics->LogEvent(Name, Parameters);
		}
	}
}

void UUltimateMobileKitAnalytics::LogEventString(const FString& Name, const FString& ParameterName, const FString& ParameterValue)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAnalyticsPtr FirebaseAnalytics = UltimateMobileKit->GetFirebaseAnalytics();

		if (FirebaseAnalytics.IsValid())
		{
			FirebaseAnalytics->LogEventString(Name, ParameterName, ParameterValue);
		}
	}
}

void UUltimateMobileKitAnalytics::LogEventInteger(const FString& Name, const FString& ParameterName, const int32 ParameterValue)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAnalyticsPtr FirebaseAnalytics = UltimateMobileKit->GetFirebaseAnalytics();

		if (FirebaseAnalytics.IsValid())
		{
			FirebaseAnalytics->LogEventInteger(Name, ParameterName, ParameterValue);
		}
	}
}

void UUltimateMobileKitAnalytics::LogEventFloat(const FString& Name, const FString& ParameterName, const float ParameterValue)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAnalyticsPtr FirebaseAnalytics = UltimateMobileKit->GetFirebaseAnalytics();

		if (FirebaseAnalytics.IsValid())
		{
			FirebaseAnalytics->LogEventFloat(Name, ParameterName, ParameterValue);
		}
	}
}

void UUltimateMobileKitAnalytics::SetUserId(const FString& UserId)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAnalyticsPtr FirebaseAnalytics = UltimateMobileKit->GetFirebaseAnalytics();

		if (FirebaseAnalytics.IsValid())
		{
			FirebaseAnalytics->SetUserId(UserId);
		}
	}
}

void UUltimateMobileKitAnalytics::SetUserProperty(const FString& Name, const FString& Property)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAnalyticsPtr FirebaseAnalytics = UltimateMobileKit->GetFirebaseAnalytics();

		if (FirebaseAnalytics.IsValid())
		{
			FirebaseAnalytics->SetUserProperty(Name, Property);
		}
	}
}

void UUltimateMobileKitAnalytics::SetCurrentScreen(const FString& ScreenName, const FString& ScreenClass)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAnalyticsPtr FirebaseAnalytics = UltimateMobileKit->GetFirebaseAnalytics();

		if (FirebaseAnalytics.IsValid())
		{
			FirebaseAnalytics->SetCurrentScreen(ScreenName, ScreenClass);
		}
	}
}

void UUltimateMobileKitAnalytics::ResetAnalyticsData()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAnalyticsPtr FirebaseAnalytics = UltimateMobileKit->GetFirebaseAnalytics();

		if (FirebaseAnalytics.IsValid())
		{
			FirebaseAnalytics->ResetAnalyticsData();
		}
	}
}

void UUltimateMobileKitAnalytics::SetAnalyticsCollectionEnabled(bool bEnabled)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAnalyticsPtr FirebaseAnalytics = UltimateMobileKit->GetFirebaseAnalytics();

		if (FirebaseAnalytics.IsValid())
		{
			FirebaseAnalytics->SetAnalyticsCollectionEnabled(bEnabled);
		}
	}
}
