// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MorseEngineSubsystem.h"

void UMorseEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);


	m_DefaultParticipant = NewObject<UDDSParticipant>(this);
	m_DefaultParticipant->Init();
};

void UMorseEngineSubsystem::Deinitialize()
{

}

UDDSParticipant* UMorseEngineSubsystem::GetDefaultParticipant()
{
    return m_DefaultParticipant;
};