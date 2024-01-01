// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "UltimateMobileKitModule.h"
#include "UltimateMobileKit.h"
#include "ISettingsModule.h"
#include "UltimateMobileKitSettings.h"

#define LOCTEXT_NAMESPACE "UltimateMobileKit"

IMPLEMENT_MODULE(FUltimateMobileKitModule, UltimateMobileKit);

/** Class responsible for creating instance(s) of the subsystem */
class FOnlineFactoryUltimateMobileKit : public IOnlineFactory
{
public:

	FOnlineFactoryUltimateMobileKit() {}
	virtual ~FOnlineFactoryUltimateMobileKit() {}

	virtual IOnlineSubsystemPtr CreateSubsystem(FName InstanceName)
	{
		UE_LOG(LogUltimateMobileKit, Log, TEXT("Ultimate Mobile Kit CreateSubsystem!"));

		FUltimateMobileKitPtr OnlineSub = MakeShareable(new FUltimateMobileKit(InstanceName));
		if (OnlineSub->IsEnabled())
		{
			if (!OnlineSub->Init())
			{
				UE_LOG(LogUltimateMobileKit, Warning, TEXT("Ultimate Mobile Kit API failed to initialize!"));
				OnlineSub->Shutdown();
				OnlineSub = NULL;
			}
		}
		else
		{
			UE_LOG(LogUltimateMobileKit, Warning, TEXT("Ultimate Mobile Kit API disabled!"));
			OnlineSub->Shutdown();
			OnlineSub = NULL;
		}

		return OnlineSub;
	}
};


void FUltimateMobileKitModule::StartupModule()
{
	UE_LOG(LogUltimateMobileKit, Log, TEXT("Ultimate Mobile Kit Startup!"));

	UltimateMobileKitFactory = new FOnlineFactoryUltimateMobileKit();

	FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
	OSS.RegisterPlatformService(TEXT("UltimateMobileKit"), UltimateMobileKitFactory);

	// Register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "UltimateMobileKit",
			LOCTEXT("RuntimeSettingsName", "Ultimate Mobile Kit"),
			LOCTEXT("RuntimeSettingsDescription", "Configure the Ultimate Mobile Kit plugin"),
			GetMutableDefault<UUltimateMobileKitSettings>()
		);
	}
}

void FUltimateMobileKitModule::ShutdownModule()
{
	UE_LOG(LogUltimateMobileKit, Log, TEXT("Ultimate Mobile Kit Shutdown!"));

	FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
	OSS.UnregisterPlatformService(TEXT("UltimateMobileKit"));

	delete UltimateMobileKitFactory;
	UltimateMobileKitFactory = NULL;

	// Unregister settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "UltimateMobileKit");
	}
}

#undef LOCTEXT_NAMESPACE
