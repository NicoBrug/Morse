// Fill out your copyright notice in the Description page of Project Settings.


#include "Participant/DDSParticipant.h"
#include "Utils/MRSLogs.h"

UDDSParticipant::UDDSParticipant(const FObjectInitializer& Initializer)
{
	Init();
};

void UDDSParticipant::Init()
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
		m_State = EEntityState::NOT_INITIALIZED;
		return;
	}

	m_State = EEntityState::INITIALIZED;
};

void UDDSParticipant::Fini()
{
	RC_DDS_CHECK(dds_delete(m_Entity)); //DDS Check return code
	m_State = EEntityState::DESTROYED;
};
