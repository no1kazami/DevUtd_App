// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Crashlytics/CrashlyticsLibrary.h"
#include "UltimateMobileKit.h"

UUltimateMobileKitCrashlytics::UUltimateMobileKitCrashlytics(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const bool UUltimateMobileKitCrashlytics::IsFirebaseCrashlyticsInitialized()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseCrashlyticsPtr FirebaseCrashlytics = UltimateMobileKit->GetFirebaseCrashlytics();

		if (FirebaseCrashlytics.IsValid())
		{
			return FirebaseCrashlytics->IsInitialized();
		}
	}

	return false;
}

void UUltimateMobileKitCrashlytics::ForceCrash()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseCrashlyticsPtr FirebaseCrashlytics = UltimateMobileKit->GetFirebaseCrashlytics();

		if (FirebaseCrashlytics.IsValid())
		{
			FirebaseCrashlytics->ForceCrash();
		}
	}
}

void UUltimateMobileKitCrashlytics::ForceException()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseCrashlyticsPtr FirebaseCrashlytics = UltimateMobileKit->GetFirebaseCrashlytics();

		if (FirebaseCrashlytics.IsValid())
		{
			FirebaseCrashlytics->ForceException();
		}
	}
}

void UUltimateMobileKitCrashlytics::SetUserIdentifier(const FString& Identifier)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseCrashlyticsPtr FirebaseCrashlytics = UltimateMobileKit->GetFirebaseCrashlytics();

		if (FirebaseCrashlytics.IsValid())
		{
			FirebaseCrashlytics->SetUserIdentifier(Identifier);
		}
	}
}

void UUltimateMobileKitCrashlytics::SetUserEmail(const FString& Email)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseCrashlyticsPtr FirebaseCrashlytics = UltimateMobileKit->GetFirebaseCrashlytics();

		if (FirebaseCrashlytics.IsValid())
		{
			FirebaseCrashlytics->SetUserEmail(Email);
		}
	}
}

void UUltimateMobileKitCrashlytics::SetUsername(const FString& Username)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseCrashlyticsPtr FirebaseCrashlytics = UltimateMobileKit->GetFirebaseCrashlytics();

		if (FirebaseCrashlytics.IsValid())
		{
			FirebaseCrashlytics->SetUsername(Username);
		}
	}
}

void UUltimateMobileKitCrashlytics::WriteLog(const FString& Log)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseCrashlyticsPtr FirebaseCrashlytics = UltimateMobileKit->GetFirebaseCrashlytics();

		if (FirebaseCrashlytics.IsValid())
		{
			FirebaseCrashlytics->WriteLog(Log);
		}
	}
}

void UUltimateMobileKitCrashlytics::WriteLogWithTagAndPriority(const FString& Log, const FString& Tag, const int32 Priority)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseCrashlyticsPtr FirebaseCrashlytics = UltimateMobileKit->GetFirebaseCrashlytics();

		if (FirebaseCrashlytics.IsValid())
		{
			FirebaseCrashlytics->WriteLogWithTagAndPriority(Log, Tag, Priority);
		}
	}
}

void UUltimateMobileKitCrashlytics::SetString(const FString& Key, const FString& Value)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseCrashlyticsPtr FirebaseCrashlytics = UltimateMobileKit->GetFirebaseCrashlytics();

		if (FirebaseCrashlytics.IsValid())
		{
			FirebaseCrashlytics->SetString(Key, Value);
		}
	}
}

void UUltimateMobileKitCrashlytics::SetBool(const FString& Key, const bool Value)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseCrashlyticsPtr FirebaseCrashlytics = UltimateMobileKit->GetFirebaseCrashlytics();

		if (FirebaseCrashlytics.IsValid())
		{
			FirebaseCrashlytics->SetBool(Key, Value);
		}
	}
}

void UUltimateMobileKitCrashlytics::SetFloat(const FString& Key, const float Value)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseCrashlyticsPtr FirebaseCrashlytics = UltimateMobileKit->GetFirebaseCrashlytics();

		if (FirebaseCrashlytics.IsValid())
		{
			FirebaseCrashlytics->SetFloat(Key, Value);
		}
	}
}

void UUltimateMobileKitCrashlytics::SetInteger(const FString& Key, const int32 Value)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseCrashlyticsPtr FirebaseCrashlytics = UltimateMobileKit->GetFirebaseCrashlytics();

		if (FirebaseCrashlytics.IsValid())
		{
			FirebaseCrashlytics->SetInteger(Key, Value);
		}
	}
}
