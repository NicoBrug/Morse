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
			ConfigureWindows();
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			ConfigureLinux();
		}
	}
	
	private void ConfigureWindows()
	{
		string IncludePath = Path.Combine(ModuleDirectory, "Windows", "Include");
		string DllPath = Path.Combine(ModuleDirectory, "Windows", "Bin", "ddsc.dll");
		string LibPath = Path.Combine(ModuleDirectory, "Windows", "Lib", "ddsc.lib");
		string TargetOutputDll = Path.Combine("$(BinaryOutputDir)", Path.GetFileName(DllPath));
		
		PublicIncludePaths.Add(IncludePath);
		PublicAdditionalLibraries.Add(LibPath);
		RuntimeDependencies.Add(TargetOutputDll, DllPath);
        
		PublicDefinitions.Add("__MINGW32__=1");
		PublicDefinitions.Add("DDSRT_WITH_FREERTOS=0");
		PublicDefinitions.Add("__GNUC__=1");
		//PublicDefinitions.Add("__clang__=1");
		PublicDefinitions.Add("__GNUC_MINOR__=3");
		PublicDefinitions.Add("__GNUC_PATCHLEVEL__=0");
		PublicDefinitions.Add("__clang_major__=12");
		PublicDefinitions.Add("__clang_minor__=0");
		PublicDefinitions.Add("__clang_patchlevel__=0");
	}

	private void ConfigureLinux()
	{
		string IncludePath = Path.Combine(ModuleDirectory, "Linux", "Include");
		string LibPath = Path.Combine(ModuleDirectory, "Linux", "Lib", "libddsc.so");
		string TargetOutputLib = Path.Combine("$(BinaryOutputDir)", Path.GetFileName(LibPath));

		PublicIncludePaths.Add(IncludePath);
		PublicAdditionalLibraries.Add(LibPath);
		RuntimeDependencies.Add(TargetOutputLib, LibPath);

		PublicDefinitions.Add("_WIN32=0");
		PublicDefinitions.Add("__MINGW32__=0");
		PublicDefinitions.Add("__VXWORKS__=0");
		PublicDefinitions.Add("DDSRT_WITH_FREERTOS=0");
		PublicDefinitions.Add("__STDC_VERSION__=201710L");
		PublicDefinitions.Add("__clang__=1");
		PublicDefinitions.Add("__clang_minor__=0");
	}
}
