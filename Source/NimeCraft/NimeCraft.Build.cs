// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NimeCraft : ModuleRules
{
	public NimeCraft(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"NimeCraft",
			"NimeCraft/Variant_Platforming",
			"NimeCraft/Variant_Platforming/Animation",
			"NimeCraft/Variant_Combat",
			"NimeCraft/Variant_Combat/AI",
			"NimeCraft/Variant_Combat/Animation",
			"NimeCraft/Variant_Combat/Gameplay",
			"NimeCraft/Variant_Combat/Interfaces",
			"NimeCraft/Variant_Combat/UI",
			"NimeCraft/Variant_SideScrolling",
			"NimeCraft/Variant_SideScrolling/AI",
			"NimeCraft/Variant_SideScrolling/Gameplay",
			"NimeCraft/Variant_SideScrolling/Interfaces",
			"NimeCraft/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
