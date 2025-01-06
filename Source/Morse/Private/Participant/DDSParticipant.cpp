// Fill out your copyright notice in the Description page of Project Settings.


#include "Participant/DDSParticipant.h"
#include "Utils/MRSLogs.h"

UDDSParticipant::UDDSParticipant(const FObjectInitializer& Initializer)
{
	Initialize();
};

void UDDSParticipant::Initialize()
{
	//dds_domainid_t DomainId = 1;
	//dds_entity_t DomainEntity = dds_create_domain(DomainId, );
	
	EntityHandler = dds_create_participant
	(
		DDS_DOMAIN_DEFAULT, 
		NULL, 
		NULL
	);

	RC_DDS_CHECK(EntityHandler); //DDS Check return code
	
	if (EntityHandler < 0)
	{
		SetState(EEntityState::NOT_INITIALIZED);
		return;
	}

	SetState(EEntityState::INITIALIZED);
};

void UDDSParticipant::Terminate()
{
	RC_DDS_CHECK(dds_delete(EntityHandler)); //DDS Check return code
	SetState(EEntityState::DESTROYED);
};
