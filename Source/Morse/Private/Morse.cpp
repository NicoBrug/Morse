#include "Morse.h"

#define LOCTEXT_NAMESPACE "FMorseModule"

void FMorseModule::StartupModule()
{

};

void FMorseModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMorseModule, Morse)