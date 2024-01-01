// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Config/ConfigInitialize.h"
#include "UltimateMobileKit.h"
#include "UltimateMobileKitSettings.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
#include "firebase/remote_config.h"
#include "firebase/util.h"
#include "firebase/future.h"
#endif

FFirebaseConfigInitialize::FFirebaseConfigInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseConfigInitializeCompleteDelegate& InDelegate, const TArray<UFirebaseVariant*> InDefaultParameters, const FString& InConfigNamespace)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, DefaultParameters(InDefaultParameters)
	, ConfigNamespace(InConfigNamespace)
{
}

void FFirebaseConfigInitialize::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseConfigInitialize async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
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
					return firebase::remote_config::Initialize(*app);
				});

				return;
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseConfigInitialize::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	firebase::Future<void> LastResult = Initializer.InitializeLastResult();
	if (LastResult.status() == firebase::kFutureStatusComplete)
	{
		if (LastResult.error() == 0)
		{
			bWasSuccessful = true;
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseConfigInitialize Error: %s"), *FString(LastResult.error_message()));
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

void FFirebaseConfigInitialize::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseConfigInitialize async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful);
}

void FFirebaseConfigInitialize::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_REMOTECONFIG
	// Settings
	const UUltimateMobileKitSettings* DefaultSettings = GetDefault<UUltimateMobileKitSettings>();

	// Developer Mode
	if (DefaultSettings->bEnableRemoteConfigDeveloperMode)
	{
		firebase::remote_config::SetConfigSetting(firebase::remote_config::kConfigSettingDeveloperMode, "1");
	}

	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config developer mode %s"), DefaultSettings->bEnableRemoteConfigDeveloperMode ? TEXT("enabled") : TEXT("disabled"));

	// Default Parameters
	firebase::remote_config::ConfigKeyValueVariant* RemoteConfigDefaults = new firebase::remote_config::ConfigKeyValueVariant[DefaultParameters.Num()];
	std::string* RemoteConfigDefaultsKeyRaw = new std::string[DefaultParameters.Num()];
	std::string* RemoteConfigDefaultsStringValueRaw = new std::string[DefaultParameters.Num()];

	FString DefaultParametersString;

	for (int i = 0; i < DefaultParameters.Num(); i++)
	{
		if (DefaultParameters[i]->GetType() == EFirebaseVariantType::String)
		{
			RemoteConfigDefaultsKeyRaw[i] = std::string(TCHAR_TO_UTF8(*DefaultParameters[i]->GetName()));
			RemoteConfigDefaultsStringValueRaw[i] = std::string(TCHAR_TO_UTF8(*DefaultParameters[i]->GetStringVariant()));

			RemoteConfigDefaults[i].key = RemoteConfigDefaultsKeyRaw[i].c_str();
			RemoteConfigDefaults[i].value = RemoteConfigDefaultsStringValueRaw[i].c_str();

			DefaultParametersString += "(" + DefaultParameters[i]->GetName() + ":" + DefaultParameters[i]->GetStringVariant() + ")";
		}
		else if (DefaultParameters[i]->GetType() == EFirebaseVariantType::Integer)
		{
			RemoteConfigDefaultsKeyRaw[i] = std::string(TCHAR_TO_UTF8(*DefaultParameters[i]->GetName()));

			RemoteConfigDefaults[i].key = RemoteConfigDefaultsKeyRaw[i].c_str();
			RemoteConfigDefaults[i].value = (int) DefaultParameters[i]->GetIntegerVariant();

			DefaultParametersString += "(" + DefaultParameters[i]->GetName() + ":" + FString::FromInt(DefaultParameters[i]->GetIntegerVariant()) + ")";
		}
		else if (DefaultParameters[i]->GetType() == EFirebaseVariantType::Boolean)
		{
			RemoteConfigDefaultsKeyRaw[i] = std::string(TCHAR_TO_UTF8(*DefaultParameters[i]->GetName()));

			RemoteConfigDefaults[i].key = RemoteConfigDefaultsKeyRaw[i].c_str();
			RemoteConfigDefaults[i].value = DefaultParameters[i]->GetBooleanVariant();

			DefaultParametersString += "(" + DefaultParameters[i]->GetName() + ":" + (DefaultParameters[i]->GetBooleanVariant() ? "true" : "false") + ")";
		}
		else if (DefaultParameters[i]->GetType() == EFirebaseVariantType::Float)
		{
			RemoteConfigDefaultsKeyRaw[i] = std::string(TCHAR_TO_UTF8(*DefaultParameters[i]->GetName()));

			RemoteConfigDefaults[i].key = RemoteConfigDefaultsKeyRaw[i].c_str();
			RemoteConfigDefaults[i].value = (double) DefaultParameters[i]->GetFloatVariant();

			DefaultParametersString += "(" + DefaultParameters[i]->GetName() + ":" + FString::SanitizeFloat(DefaultParameters[i]->GetFloatVariant()) + ")";
		}

		if (i != DefaultParameters.Num() - 1)
		{
			DefaultParametersString += ", ";
		}
	}

	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config default parameters: %s"), *DefaultParametersString);

	if (ConfigNamespace.Len() == 0)
	{
		firebase::remote_config::SetDefaults(RemoteConfigDefaults, DefaultParameters.Num());

		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config default config namespace"));
	}
	else
	{
		firebase::remote_config::SetDefaults(RemoteConfigDefaults, DefaultParameters.Num(), TCHAR_TO_UTF8(*ConfigNamespace));

		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Config namespace: %s"), *ConfigNamespace);
	}

	delete[] RemoteConfigDefaultsKeyRaw;
	RemoteConfigDefaultsKeyRaw = NULL;
	delete[] RemoteConfigDefaultsStringValueRaw;
	RemoteConfigDefaultsStringValueRaw = NULL;
	delete[] RemoteConfigDefaults;
	RemoteConfigDefaults = NULL;
	
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseConfigPtr FirebaseConfig = UltimateMobileKit->GetFirebaseConfig();

		if (FirebaseConfig.IsValid())
		{
			FirebaseConfig->SetInitialized(bWasSuccessful);
		}
	}
#endif
}
