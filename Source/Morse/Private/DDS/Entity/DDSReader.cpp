#include "DDS/Entity/DDSReader.h"

#include "DDS/QoS/DDSQoS.h"
#include "Utils/MRSLogs.h"


UDDSReader::UDDSReader(const FObjectInitializer& Initializer)
{
	SetType(EEntityType::DDS_READER);
}

void UDDSReader::Initialize()
{
	if (!IsValid(OwnerParticipant))
	{
		SetState(EEntityState::NOT_INITIALIZED);
		return;
	};

	if (!IsValid(Topic))
	{
		SetState(EEntityState::NOT_INITIALIZED);
		return;
	};

	dds_qos_t* Qos = dds_create_qos();

	QoSUtils::SetQos(GetQoS(), *Qos);

	//Listener = dds_create_listener(NULL);
	//dds_lset_data_available_arg(Listener, DataAvailableHandler, this, false); 

	EntityHandler = dds_create_reader
	(
		OwnerParticipant->GetEntity(),
		Topic->GetEntity(),
		Qos,
		Listener
	);

	RC_DDS_CHECK(EntityHandler); //DDS Check return code
	
	if (EntityHandler < 0)
	{
		switch (EntityHandler)
		{
		case DDS_RETCODE_ERROR:
			UE_LOG(LogMorse, Log, TEXT("Can't initialize Reader :An internal error occurred."))
			break;
		default:
			break;
		}

		SetState(EEntityState::NOT_INITIALIZED);
	}
	else
	{
		SetState(EEntityState::INITIALIZED);
	};
};

void UDDSReader::Terminate()
{
	dds_delete_listener(Listener);
	
	if (Topic)
	{
		Topic->Terminate();
	};
	
	RC_DDS_CHECK(dds_delete(EntityHandler));

	SetState(EEntityState::DESTROYED);
};

UDDSTopic* UDDSReader::GetTopic()
{
	return Topic;
}

void UDDSReader::SetTopic(UDDSTopic* ReaderTopic)
{
	Topic = ReaderTopic;
}

void UDDSReader::SetParticipant(UDDSParticipant* InOwnerParticipant)
{
	OwnerParticipant = InOwnerParticipant;
};

void UDDSReader::Read()
{
	int Rc = 0;

	if (!IsValid(Topic))
		return;

	dds_sample_info_t infos[1];

	void* Data = Topic->GetTopicProxy()->Get();
	Rc = dds_read
	(
		EntityHandler,
		&Data,
		infos,
		Topic->GetTopicProxy()->GetTypeDesc()->m_size,
		1
	);
	
	RC_DDS_CHECK(Rc); //DDS Check return code
}

void UDDSReader::Take()
{
	int Rc = 0;

	if (!IsValid(Topic))
		return;

	dds_sample_info_t infos[1];

	void* Data = Topic->GetTopicProxy()->Get();
	Rc = dds_take
	(
		EntityHandler,
		&Data,
		infos,
		Topic->GetTopicProxy()->GetTypeDesc()->m_size,
		1
	);
	
	RC_DDS_CHECK(Rc); //DDS Check return code
};


