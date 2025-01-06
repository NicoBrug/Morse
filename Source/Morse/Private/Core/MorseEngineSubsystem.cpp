#include "Core/MorseEngineSubsystem.h"

void UMorseEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);


	m_DefaultParticipant = NewObject<UDDSParticipant>(this);
	m_DefaultParticipant->Initialize();
};

void UMorseEngineSubsystem::Deinitialize()
{
	if(m_DefaultParticipant)
	{
		m_DefaultParticipant->Terminate();
	}
}

UDDSParticipant* UMorseEngineSubsystem::GetDefaultParticipant()
{
    return m_DefaultParticipant;
};