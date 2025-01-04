// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MorseBlueprintLib : ModuleRules
{
	public MorseBlueprintLib(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"BlueprintGraph",
				"UnrealEd",
				"SlateCore",
				"KismetWidgets",
				"BlueprintGraph",
                "KismetCompiler",
				"Morse"
            }
            );

		bUseRTTI = true;  
		bEnableExceptions = true;
	}
}
