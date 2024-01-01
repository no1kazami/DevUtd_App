// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "EngineMinimal.h"
#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUltimateMobileKitEditor, Log, All);

/** Implementation of Ultimate Mobile Kit features for editor only */
class FUltimateMobileKitEditorModule : public IModuleInterface
{

public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
