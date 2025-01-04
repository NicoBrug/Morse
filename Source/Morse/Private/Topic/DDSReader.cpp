// Fill out your copyright notice in the Description page of Project Settings.


#include "Topic/DDSReader.h"
#include <Logging/StructuredLog.h>
#include "Utils/MRSLogs.h"


UDDSReader::UDDSReader(const FObjectInitializer& Initializer)
{
	m_Type = EEntityType::READER;
}

void UDDSReader::BeginDestroy()
{
	Fini();

	UE_LOG(LogTemp, Log, TEXT("Reader destroyed"));

	Super::BeginDestroy();
};

void UDDSReader::Init()
{
	if (!IsValid(m_OwnerParticipant))
	{
		m_State = EEntityState::NOT_INITIALIZED;
		return;
	};

	if (!IsValid(m_ReaderTopic))
	{
		m_State = EEntityState::NOT_INITIALIZED;
		return;
	};

	dds_qos_t* Qos = dds_create_qos();

	QoSUtils::SetQos(m_CurrentQoS, *Qos);

	rd_listener = dds_create_listener(NULL);
	dds_lset_data_available_arg(rd_listener, DataAvailableHandler, this, false); 

	m_Entity = dds_create_reader
	(
		m_OwnerParticipant->GetEntity(),
		m_ReaderTopic->GetEntity(),
		Qos,
		rd_listener
	);

	RC_DDS_CHECK(m_Entity); //DDS Check return code
	
	if (m_Entity < 0)
	{
		switch (m_Entity)
		{
		case DDS_RETCODE_ERROR:
			UE_LOG(LogTemp, Log, TEXT("Can't initialize Reader :An internal error occurred."))
				break;
		default:
			break;
		}

		m_State = EEntityState::NOT_INITIALIZED;
	}
	else
	{
		m_State = EEntityState::INITIALIZED;
	};
};

void UDDSReader::Fini()
{
	dds_delete_listener(rd_listener);
	
	if (m_ReaderTopic)
	{
		m_ReaderTopic->Fini();
	};

	dds_delete(m_Entity);
}

void UDDSReader::Read()
{
	int rc = 0;

	if (!IsValid(m_ReaderTopic))
		return;

	dds_sample_info_t infos[1];

	void* data = m_ReaderTopic->GetTopicProxy()->Get();
	rc = dds_read
	(
		m_Entity,
		&data,
		infos,
		m_ReaderTopic->GetTopicProxy()->GetTypeDesc()->m_size,
		1
	);
	
	RC_DDS_CHECK(rc); //DDS Check return code
};


