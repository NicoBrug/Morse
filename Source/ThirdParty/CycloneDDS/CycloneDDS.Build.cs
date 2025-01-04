// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class CycloneDDS : ModuleRules
{
	public CycloneDDS(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{

            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "includes"));

			var DllPath = Path.Combine(ModuleDirectory, "x64", "Release", "ddsc.dll");
			var LibPath = Path.Combine(ModuleDirectory, "x64", "Release", "ddsc.lib");
			
            // Add the import library
            PublicAdditionalLibraries.Add(LibPath);

			// Delay-load the DLL, so we can load it from the right place first

            var TargetOutputDll = Path.Combine("$(ProjectDir)\\Binaries\\ThirdParty\\", Path.GetFileName(DllPath));


            // Ensure that the DLL is staged along with the executable
            RuntimeDependencies.Add(TargetOutputDll, DllPath);

            PublicDelayLoadDLLs.Add(DllPath);


            PublicDefinitions.Add("__MINGW32__=1");

            PublicDefinitions.Add("DDSRT_WITH_FREERTOS=0");

            //// Définition des macros pour le compilateur GCC
            PublicDefinitions.Add("__GNUC__=1");

            //// Définition des macros pour le compilateur Clang
            PublicDefinitions.Add("__clang__=1");

            //// Valeurs cohérentes pour les macros GCC/Clang
            PublicDefinitions.Add("__GNUC_MINOR__=3");
            PublicDefinitions.Add("__GNUC_PATCHLEVEL__=0");
            PublicDefinitions.Add("__clang_major__=12");
            PublicDefinitions.Add("__clang_minor__=0");
            PublicDefinitions.Add("__clang_patchlevel__=0");
        }
	}
}
