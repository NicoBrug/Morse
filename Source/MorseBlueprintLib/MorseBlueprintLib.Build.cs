// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MorseBlueprintLib : ModuleRules
{
	public MorseBlueprintLib(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[] { 
				"Core", 
				"CoreUObject", 
				"Engine",
				"InputCore",
				"Slate",
				"DeveloperSettings"
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"BlueprintGraph",
				"UnrealEd",
				"SlateCore",
				"KismetWidgets",
				"BlueprintGraph",
                "KismetCompiler",
				"Morse"
            }
		);
	}
}
