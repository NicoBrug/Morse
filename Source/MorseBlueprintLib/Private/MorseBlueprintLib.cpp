// Copyright Epic Games, Inc. All Rights Reserved.

#include "MorseBlueprintLib.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FMorseBlueprintLibModule"

void FMorseBlueprintLibModule::StartupModule()
{
}

void FMorseBlueprintLibModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMorseBlueprintLibModule, MorseBlueprintLib)
