// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "UltimateMobileKitEditor.h"
#include "ISettingsModule.h"
#include "PropertyEditorModule.h"
#include "UltimateMobileKitSettingsCustomization.h"
#include "UltimateMobileKitSettings.h"

#define LOCTEXT_NAMESPACE "FUltimateMobileKitEditorModule"

IMPLEMENT_MODULE(FUltimateMobileKitEditorModule, UltimateMobileKitEditor);

void FUltimateMobileKitEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(
		UUltimateMobileKitSettings::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(&FUltimateMobileKitSettingsCustomization::MakeInstance)
	);

	PropertyModule.NotifyCustomizationModuleChanged();

	UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("Ultimate Mobile Kit Editor module started"));
}

void FUltimateMobileKitEditorModule::ShutdownModule()
{
	UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("Ultimate Mobile Kit Editor module shutdown"));
}

#undef LOCTEXT_NAMESPACE
