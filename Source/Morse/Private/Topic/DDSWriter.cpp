// Fill out your copyright notice in the Description page of Project Settings.


#include "Topic/DDSWriter.h"
#include <Utils/MRSLogs.h>


UDDSWriter::UDDSWriter(const FObjectInitializer& Initializer)
{
	m_Type = EEntityType::WRITER;
}

void UDDSWriter::BeginDestroy()
{
	Fini();
	
	Super::BeginDestroy();
}

void UDDSWriter::Init()
{
	if (!IsValid(m_OwnerParticipant))
	{
		m_State = EEntityState::NOT_INITIALIZED;
		return;
	}

	if (!IsValid(m_WriterTopic))
	{
		m_State = EEntityState::NOT_INITIALIZED;
		return;
	};

	dds_qos_t* Qos = dds_create_qos();

	QoSUtils::SetQos(m_CurrentQoS, *Qos);

	m_Entity = dds_create_writer
	(
		m_OwnerParticipant->GetEntity(),
		m_WriterTopic->GetEntity(),
		Qos,
		NULL
	);
	
	RC_DDS_CHECK(m_Entity);

	dds_delete_qos(Qos);

	dds_set_status_mask(m_Entity, DDS_PUBLICATION_MATCHED_STATUS);

	m_State = EEntityState::INITIALIZED;
}

void UDDSWriter::Fini()
{
	if (m_WriterTopic)
	{
		UE_LOG(LogTemp, Log, TEXT("Writer topic fini"));

		m_WriterTopic->Fini();
	};

	RC_DDS_CHECK(dds_delete(m_Entity));
}

void UDDSWriter::Write()
{
	int rc = 0;

	// If we found a compatible reader (topic & QoS) we set value of this topic on DDS.
	if (!(m_uiStatus & DDS_PUBLICATION_MATCHED_STATUS))
	{
		rc = dds_get_status_changes(m_Entity, &m_uiStatus);
		if (rc != DDS_RETCODE_OK)
			return;
	}

	if (!m_WriterTopic->IsValidLowLevel())
		return;

	if (!m_WriterTopic->GetTopicProxy())
		return;

	if (!m_WriterTopic->GetTopicProxy()->Get())
		return;
	
	//Write data on DDS
	rc = dds_write
	(
		m_Entity,
		m_WriterTopic->GetTopicProxy()->Get()
	);
	
	RC_DDS_CHECK(rc); //DDS Check return code
};