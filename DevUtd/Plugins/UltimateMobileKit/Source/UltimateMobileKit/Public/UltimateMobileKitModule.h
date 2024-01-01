// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "EngineMinimal.h"

/** Online subsystem module class (Firebase Implementation). Code related to the loading and handling of the Ultimate Mobile Kit module. */
class FUltimateMobileKitModule : public IModuleInterface
{
private:
	class FOnlineFactoryUltimateMobileKit* UltimateMobileKitFactory;

public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool SupportsDynamicReloading() override
	{
		return false;
	}
	virtual bool SupportsAutomaticShutdown() override
	{
		return false;
	}

	FUltimateMobileKitModule() :
		UltimateMobileKitFactory(NULL)
	{}

	virtual ~FUltimateMobileKitModule()
	{}
};
