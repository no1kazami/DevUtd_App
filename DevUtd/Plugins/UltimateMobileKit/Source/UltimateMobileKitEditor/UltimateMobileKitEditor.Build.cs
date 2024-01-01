// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class UltimateMobileKitEditor : ModuleRules
	{
		public UltimateMobileKitEditor(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

			PrivateIncludePaths.AddRange(new string[] { "UltimateMobileKitEditor/Private" });

			PublicDependencyModuleNames.AddRange(new string[]{ "Core", "Projects" });

			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"Core",
					"CoreUObject",
					"Engine",
                    "UnrealEd",
					"Slate",
					"SlateCore",
					"EditorStyle",
					"EditorWidgets",
					"PropertyEditor",
					"SharedSettingsWidgets",
					"SourceControl",
					"XmlParser",
					"UltimateMobileKit"
				}
			);

			PrivateIncludePathModuleNames.AddRange(new string[] { "Settings" });
		}
	}
}
