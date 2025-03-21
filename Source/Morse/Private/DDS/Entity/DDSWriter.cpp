#include "DDS/Entity/DDSWriter.h"
#include <Utils/MRSLogs.h>
#include "DDS/Entity/DDSTopic.h"

#include "DDS/QoS/DDSQoS.h"


UDDSWriter::UDDSWriter(const FObjectInitializer& Initializer)
{
	SetType(EEntityType::DDS_WRITER);
};

void UDDSWriter::Initialize()
{
	if (!IsValid(OwnerParticipant))
	{
		SetState(EEntityState::NOT_INITIALIZED);
		return;
	}

	if (!IsValid(Topic))
	{
		SetState(EEntityState::NOT_INITIALIZED);
		return;
	};

	dds_qos_t* Qos = dds_create_qos();

	QoSUtils::SetQos(GetQoS(), *Qos);

	EntityHandler = dds_create_writer
	(
		OwnerParticipant->GetEntity(),
		Topic->GetEntity(),
		Qos,
		NULL
	);
	
	RC_DDS_CHECK(EntityHandler);

	dds_delete_qos(Qos);

	dds_set_status_mask(EntityHandler, DDS_PUBLICATION_MATCHED_STATUS);

	SetState(EEntityState::INITIALIZED);
}

void UDDSWriter::Terminate()
{
	if (Topic)
	{
		Topic->Terminate();
		UE_LOG(LogMorse, Log, TEXT("Writer topic Terminated"));
	};

	RC_DDS_CHECK(dds_delete(EntityHandler));

	SetState(EEntityState::DESTROYED);
}

UDDSTopic* UDDSWriter::GetTopic()
{
	return Topic;
}

void UDDSWriter::SetTopic(UDDSTopic* WriterTopic)
{
	Topic = WriterTopic;
}

void UDDSWriter::SetParticipant(UDDSParticipant* InOwnerParticipant)
{
	OwnerParticipant = InOwnerParticipant;
};

void UDDSWriter::Write()
{
	int Rc = 0;

	// If we found a compatible reader (topic & QoS) we set value of this topic on DDS.
	if (!(EntityDDSStatus & DDS_PUBLICATION_MATCHED_STATUS))
	{
		Rc = dds_get_status_changes(EntityHandler, &EntityDDSStatus);
		if (Rc != DDS_RETCODE_OK)
			return;
	}

	if (!Topic->IsValidLowLevel())
		return;

	if (!Topic->GetTopicProxy())
		return;

	if (!Topic->GetTopicProxy()->Get())
		return;
	
	//Write data on DDS
	Rc = dds_write
	(
		EntityHandler,
		Topic->GetTopicProxy()->Get()
	);
	
	RC_DDS_CHECK(Rc); //DDS Check return code
};