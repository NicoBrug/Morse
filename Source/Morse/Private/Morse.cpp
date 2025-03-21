#include "Morse.h"
#include "Core/MRSSettings.h"
#include "ISettingsModule.h"

#define LOCTEXT_NAMESPACE "FMorseModule"

void FMorseModule::StartupModule()
{
	if(ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "DDSPluginSettings",
			LOCTEXT("RuntimeSettingsName", "Morse"), LOCTEXT("RuntimeSettingsDescription", "Configure my setting"),
			GetMutableDefault<UMRSSettings>());
	};
};

void FMorseModule::ShutdownModule()
{
	if(ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "DDSPluginSettings");
	};
};

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMorseModule, Morse)