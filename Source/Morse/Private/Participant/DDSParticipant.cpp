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
	
	m_Entity = dds_create_participant
	(
		DDS_DOMAIN_DEFAULT, 
		NULL, 
		NULL
	);

	RC_DDS_CHECK(m_Entity); //DDS Check return code
	
	if (m_Entity < 0)
	{
		SetState(EEntityState::NOT_INITIALIZED);
		return;
	}

	SetState(EEntityState::INITIALIZED);
};

void UDDSParticipant::Terminate()
{
	RC_DDS_CHECK(dds_delete(m_Entity)); //DDS Check return code
	SetState(EEntityState::DESTROYED);
};
