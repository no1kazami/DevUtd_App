// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Config/ConfigLibrary.h"
#include "UltimateMobileKit.h"

UUltimateMobileKitConfig::UUltimateMobileKitConfig(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UUltimateMobileKitConfig::IsFirebaseConfigInitialized()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseConfigPtr FirebaseConfig = UltimateMobileKit->GetFirebaseConfig();

		if (FirebaseConfig.IsValid())
		{
			return FirebaseConfig->IsInitialized();
		}
	}

	return false;
}

bool UUltimateMobileKitConfig::ActivateFetched()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseConfigPtr FirebaseConfig = UltimateMobileKit->GetFirebaseConfig();

		if (FirebaseConfig.IsValid())
		{
			return FirebaseConfig->ActivateFetched();
		}
	}

	return false;
}

TArray<FString> UUltimateMobileKitConfig::GetKeys(const FString& ConfigNamespace)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseConfigPtr FirebaseConfig = UltimateMobileKit->GetFirebaseConfig();

		if (FirebaseConfig.IsValid())
		{
			return FirebaseConfig->GetKeys(ConfigNamespace);
		}
	}

	return TArray<FString>();
}

TArray<FString> UUltimateMobileKitConfig::GetKeysByPrefix(const FString& Prefix, const FString& ConfigNamespace)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseConfigPtr FirebaseConfig = UltimateMobileKit->GetFirebaseConfig();

		if (FirebaseConfig.IsValid())
		{
			return FirebaseConfig->GetKeysByPrefix(Prefix, ConfigNamespace);
		}
	}

	return TArray<FString>();
}

const FRemoteConfigInfo UUltimateMobileKitConfig::GetInfo()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseConfigPtr FirebaseConfig = UltimateMobileKit->GetFirebaseConfig();

		if (FirebaseConfig.IsValid())
		{
			return FirebaseConfig->GetInfo();
		}
	}

	return FRemoteConfigInfo();
}

bool UUltimateMobileKitConfig::GetBoolean(const FString& Name, const FString& ConfigNamespace)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseConfigPtr FirebaseConfig = UltimateMobileKit->GetFirebaseConfig();

		if (FirebaseConfig.IsValid())
		{
			return FirebaseConfig->GetBoolean(Name, ConfigNamespace);
		}
	}

	return false;
}

float UUltimateMobileKitConfig::GetFloat(const FString& Name, const FString& ConfigNamespace)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseConfigPtr FirebaseConfig = UltimateMobileKit->GetFirebaseConfig();

		if (FirebaseConfig.IsValid())
		{
			return FirebaseConfig->GetFloat(Name, ConfigNamespace);
		}
	}

	return 0;
}

const int32 UUltimateMobileKitConfig::GetInteger(const FString& Name, const FString& ConfigNamespace)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseConfigPtr FirebaseConfig = UltimateMobileKit->GetFirebaseConfig();

		if (FirebaseConfig.IsValid())
		{
			return FirebaseConfig->GetInteger(Name, ConfigNamespace);
		}
	}

	return 0;
}

const FString UUltimateMobileKitConfig::GetString(const FString& Name, const FString& ConfigNamespace)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseConfigPtr FirebaseConfig = UltimateMobileKit->GetFirebaseConfig();

		if (FirebaseConfig.IsValid())
		{
			return FirebaseConfig->GetString(Name, ConfigNamespace);
		}
	}

	return FString();
}
