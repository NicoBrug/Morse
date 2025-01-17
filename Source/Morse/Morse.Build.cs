// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Morse : ModuleRules
{
	public Morse(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "CycloneDDS",
                "CinematicCamera",
                "SlateCore",
                "UMG",
                "Settings",
                "DeveloperSettings",
                "WebSockets",
                "Json",
                "Sockets",
                "WebSocketNetworking"
			}
            );
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore", "XmlParser",
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
