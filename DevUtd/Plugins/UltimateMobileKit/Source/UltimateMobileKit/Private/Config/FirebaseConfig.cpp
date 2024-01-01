// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Config/FirebaseConfig.h"
#include "UltimateMobileKitSettings.h"
#include "UltimateMobileKit.h"
#include "Config/ConfigInitialize.h"
#include "Config/ConfigFetch.h"

FFirebaseConfig::FFirebaseConfig()
{
}

FFirebaseConfig::~FFirebaseConfig()
{
}

void FFirebaseConfig::Init(const TArray<UFirebaseVariant*> DefaultParameters, const FString& ConfigNamespace /*= FString()*/, const FOnFirebaseConfigInitializeCompleteDelegate& Delegate /*= FOnFirebaseConfigInitializeCompleteDelegate()*/)
{
	if (IsInitialized())
	{
		Delegate.ExecuteIfBound(true);
		return;
	}

	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		auto QueryTask = new FFirebaseConfigInitialize(UltimateMobileKit->Get(), Delegate, DefaultParameters, ConfigNamespace);
		UltimateMobileKit->QueueAsyncTask(QueryTask);

		return;
	}

	Delegate.ExecuteIfBound(false);
}

void FFirebaseConfig::Shutdown()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config Shutdown"));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	firebase::remote_config::Terminate();
#endif
}

const bool FFirebaseConfig::IsInitialized() const
{
	return bInitialized;
}

void FFirebaseConfig::SetInitialized(bool Initialized)
{
	bInitialized = Initialized;

	if (bInitialized)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config is initialized successfully"));
	}
	else
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config is not initialized"));
	}
}

void FFirebaseConfig::Fetch(const FOnFirebaseConfigFetchCompleteDelegate& Delegate /*= FOnFirebaseConfigFetchCompleteDelegate()*/, const int32 CacheExpirationInSeconds /*= 0*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseConfigFetch(UltimateMobileKit->Get(), Delegate, CacheExpirationInSeconds);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false);
}

const bool FFirebaseConfig::ActivateFetched() const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	if (IsInitialized())
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config activate fetched"));

		return firebase::remote_config::ActivateFetched();
	}
#endif

	return false;
}

const TArray<FString> FFirebaseConfig::GetKeys(const FString& ConfigNamespace /*= FString()*/) const
{
	TArray<FString> KeysArray;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	if (IsInitialized())
	{
		std::vector<std::string> Keys;

		if (ConfigNamespace.Len() == 0)
		{
			Keys = firebase::remote_config::GetKeys();

			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config get keys for default namespace"));
		}
		else
		{
			Keys = firebase::remote_config::GetKeys(TCHAR_TO_UTF8(*ConfigNamespace));

			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config get keys for namespace: %s"), *ConfigNamespace);
		}

		FString KeysString;
		for (auto Key = Keys.begin(); Key != Keys.end(); ++Key) 
		{
			KeysArray.Add(FString(Key->c_str()));

			KeysString += FString(Key->c_str());

			if (Key != Keys.end())
			{
				KeysString += ", ";
			}
		}

		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config retrieved keys: %s"), *KeysString);
	}
#endif

	return KeysArray;
}

const TArray<FString> FFirebaseConfig::GetKeysByPrefix(const FString& Prefix, const FString& ConfigNamespace /*= FString()*/) const
{
	TArray<FString> KeysArray;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	if (IsInitialized())
	{
		std::vector<std::string> Keys; 

		if (ConfigNamespace.Len() == 0)
		{
			Keys = firebase::remote_config::GetKeysByPrefix(TCHAR_TO_UTF8(*Prefix));

			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config get keys for prefix %s for default namespace"), *Prefix);
		}
		else
		{
			Keys = firebase::remote_config::GetKeysByPrefix(TCHAR_TO_UTF8(*Prefix), TCHAR_TO_UTF8(*ConfigNamespace));

			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config get keys for prefix %s for namespace: %s"), *Prefix, *ConfigNamespace);
		}

		FString KeysString;
		for (auto Key = Keys.begin(); Key != Keys.end(); ++Key)
		{
			KeysArray.Add(FString(Key->c_str()));

			KeysString += FString(Key->c_str());

			if (Key != Keys.end())
			{
				KeysString += ", ";
			}
		}

		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config retrieved keys: %s"), *KeysString);
	}
#endif

	return KeysArray;
}

const FRemoteConfigInfo FFirebaseConfig::GetInfo() const
{
	FRemoteConfigInfo RemoteConfigInfo;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	if (IsInitialized())
	{
		const firebase::remote_config::ConfigInfo& info = firebase::remote_config::GetInfo();

		RemoteConfigInfo.FetchTime = FString::Printf(TEXT("%lld"), info.fetch_time);
		RemoteConfigInfo.ThrottledEndTime = FString::Printf(TEXT("%lld"), info.throttled_end_time);
		
		FString LastFetchFailureReason;
		FString LastFetchStatus;

		switch (info.last_fetch_failure_reason)
		{
		case firebase::remote_config::FetchFailureReason::kFetchFailureReasonError:
			RemoteConfigInfo.FetchFailureReason = EFetchFailureReason::FetchFailureReasonError;
			LastFetchFailureReason = "Error";
			break;
		case firebase::remote_config::FetchFailureReason::kFetchFailureReasonInvalid:
			RemoteConfigInfo.FetchFailureReason = EFetchFailureReason::FetchFailureReasonInvalid;
			LastFetchFailureReason = "Invalid";
			break;
		case firebase::remote_config::FetchFailureReason::kFetchFailureReasonThrottled:
			RemoteConfigInfo.FetchFailureReason = EFetchFailureReason::FetchFailureReasonThrottled;
			LastFetchFailureReason = "Throttled";
			break;
		default:
			RemoteConfigInfo.FetchFailureReason = EFetchFailureReason::FetchFailureReasonInvalid;
			LastFetchFailureReason = "Invalid";
			break;
		}
		
		switch (info.last_fetch_status)
		{
		case firebase::remote_config::LastFetchStatus::kLastFetchStatusSuccess:
			RemoteConfigInfo.LastFetchStatus = ELastFetchStatus::LastFetchStatusSuccess;
			LastFetchStatus = "Success";
			break;
		case firebase::remote_config::LastFetchStatus::kLastFetchStatusFailure:
			RemoteConfigInfo.LastFetchStatus = ELastFetchStatus::LastFetchStatusFailure;
			LastFetchStatus = "Failure";
			break;
		case firebase::remote_config::LastFetchStatus::kLastFetchStatusPending:
			RemoteConfigInfo.LastFetchStatus = ELastFetchStatus::LastFetchStatusPending;
			LastFetchStatus = "Pending";
			break;
		default:
			RemoteConfigInfo.LastFetchStatus = ELastFetchStatus::LastFetchStatusFailure;
			LastFetchStatus = "Failure";
			break;
		}

		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config get info. Fetch Time: %s, Throttled End Time: %s, Fetch Failure Reason: %s, Last Fetch Status: %s"), *RemoteConfigInfo.FetchTime, *RemoteConfigInfo.ThrottledEndTime, *LastFetchFailureReason, *LastFetchStatus);
	}
#endif

	return RemoteConfigInfo;
}

const bool FFirebaseConfig::GetBoolean(const FString& Name, const FString& ConfigNamespace /*= FString()*/) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	if (IsInitialized())
	{
		if (ConfigNamespace.Len() == 0)
		{
			bool ConfigValue = firebase::remote_config::GetBoolean(TCHAR_TO_UTF8(*Name));
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config get boolean value for key %s in default namespace: %s"), *Name, ConfigValue ? TEXT("true") : TEXT("false"));

			return ConfigValue;
		}
		else
		{
			bool ConfigValue = firebase::remote_config::GetBoolean(TCHAR_TO_UTF8(*Name), TCHAR_TO_UTF8(*ConfigNamespace));
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config get boolean value for key %s in namespace %s: %s"), *Name, *ConfigNamespace, ConfigValue ? TEXT("true") : TEXT("false"));

			return ConfigValue;
		}
	}
#endif

	return false;
}

const float FFirebaseConfig::GetFloat(const FString& Name, const FString& ConfigNamespace /*= FString()*/) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	if (IsInitialized())
	{
		if (ConfigNamespace.Len() == 0)
		{
			float ConfigValue = firebase::remote_config::GetDouble(TCHAR_TO_UTF8(*Name));
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config get double value for key %s in default namespace: %s"), *Name, *FString::SanitizeFloat(ConfigValue));

			return ConfigValue;
		}
		else
		{
			float ConfigValue = firebase::remote_config::GetDouble(TCHAR_TO_UTF8(*Name), TCHAR_TO_UTF8(*ConfigNamespace));
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config get double value for key %s in namespace %s: %s"), *Name, *ConfigNamespace, *FString::SanitizeFloat(ConfigValue));

			return ConfigValue;
		}
	}
#endif

	return 0;
}

const int32 FFirebaseConfig::GetInteger(const FString& Name, const FString& ConfigNamespace /*= FString()*/) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	if (IsInitialized())
	{
		if (ConfigNamespace.Len() == 0)
		{
			int32 ConfigValue = firebase::remote_config::GetLong(TCHAR_TO_UTF8(*Name));
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config get integer value for key %s in default namespace: %d"), *Name, ConfigValue);

			return ConfigValue;
		}
		else
		{
			int32 ConfigValue = firebase::remote_config::GetLong(TCHAR_TO_UTF8(*Name), TCHAR_TO_UTF8(*ConfigNamespace));
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config get integer value for key %s in namespace %s: %d"), *Name, *ConfigNamespace, ConfigValue);

			return ConfigValue;
		}
	}
#endif

	return 0;
}

const FString FFirebaseConfig::GetString(const FString& Name, const FString& ConfigNamespace /*= FString()*/) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	if (IsInitialized())
	{
		if (ConfigNamespace.Len() == 0)
		{
			FString ConfigValue = FString(UTF8_TO_TCHAR(firebase::remote_config::GetString(TCHAR_TO_UTF8(*Name)).c_str()));
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config get string value for key %s in default namespace: %s"), *Name, *ConfigValue);

			return ConfigValue;
		}
		else
		{
			FString ConfigValue = FString(UTF8_TO_TCHAR(firebase::remote_config::GetString(TCHAR_TO_UTF8(*Name), TCHAR_TO_UTF8(*ConfigNamespace)).c_str()));
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config get string value for key %s in namespace %s: %s"), *Name, *ConfigNamespace, *ConfigValue);

			return ConfigValue;
		}
	}
#endif

	return FString();
}
