#include "Core/MorseEngineSubsystem.h"
#include "Engine/World.h"

#include "Core/MorseSettings.h"

void UMorseEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UMorseEngineSubsystem::OnPostWorldInit);
};

void UMorseEngineSubsystem::Deinitialize()
{
	if(DefaultParticipant)
	{
		DefaultParticipant->Terminate();
	}
}

void UMorseEngineSubsystem::OnPostWorldInit(UWorld* pWorld, const UWorld::InitializationValues)
{
	DefaultParticipant = NewObject<UDDSParticipant>(this);
	DefaultParticipant->Initialize();
};

UDDSParticipant* UMorseEngineSubsystem::GetDefaultParticipant()
{
    return DefaultParticipant;
};