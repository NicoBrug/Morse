#include "Core/MRSExecutor.h"
#include "DDS/Entity/DDSReader.h"

MRSThreadedExecutor::MRSThreadedExecutor(const FTimespan& InThreadTickRate, const TCHAR* InName)
	:Super(InThreadTickRate, InName)
{
	
}

MRSThreadedExecutor::~MRSThreadedExecutor()
{
	IsRunning = false;
	Stop();
}

void MRSThreadedExecutor::ThreadTick(double dDeltaTime)
{
	Execute();
}

void MRSThreadedExecutor::Init(UDDSParticipant* Participant)
{
	Super::Init();
	WaitsetHandler = dds_create_waitset(Participant->GetEntity());
	IsRunning = true;
};

void MRSThreadedExecutor::AddEntity(UDDSEntity* Entity)
{
	m_pEntities.Add(Entity);
};

void MRSThreadedExecutor::Execute()
{
	if (!IsRunning)
		return;
	
	AttachEntitiesToWaitset();

	TArray<dds_attach_t> Triggered;
	Triggered.SetNum(m_pEntities.Num()); // Alloue dynamiquement la mémoire
	
 
	dds_return_t result = dds_waitset_wait(WaitsetHandler, Triggered.GetData(), m_pEntities.Num(), DDS_INFINITY);
	
	const int Count = result;

	if (Count < 0 ||Count == 0)
	{
		DetachAllEntitiesFromWaitset();
		return;
	}
	
	for (int i = 0; i < Count; ++i)
	{
		for (auto Entity : m_pEntities)
		{
			if (Entity->GetEntity() == Triggered[i])
			{
				HandleEntity(Entity);
				break;
			}
		}
	};
	
	DetachAllEntitiesFromWaitset();
}

void MRSThreadedExecutor::HandleEntity(UDDSEntity* Entity)
{
	if (!Entity)
		return;
 	
	switch (Entity->GetType())
	{
	case EEntityType::DDS_READER:
		uint32_t Status;
		dds_get_status_changes(Entity->GetEntity(), &Status);

		if (Status & DDS_DATA_AVAILABLE_STATUS) // Vérifie que c'est une nouvelle donnée
		{
			HandleReader(Entity);
		};
		break;
	default:
		UE_LOGFMT(LogExecutor, Warning, "Unkow Entity Type");
		break;
	};
};

void MRSThreadedExecutor::HandleReader(UDDSEntity* Entity)
{
	UDDSReader* Reader = static_cast<UDDSReader*>(Entity);
	if (!Reader || !Reader->GetTopic() || !Reader->GetTopic()->GetTopicProxy())
		return;
	
	Reader->Take();

	AsyncTask(ENamedThreads::GameThread, [Reader]()
	{
		if (Reader->GetTopic() && Reader->GetTopic()->GetTopicProxy())
		{
			Reader->GetTopic()->GetTopicProxy()->ExecuteMessageCallback();
		}
		else
		{
			UE_LOGFMT(LogExecutor, Warning, "Invalid topic proxy or reader");
		};
	});
	
};


void MRSThreadedExecutor::AttachEntitiesToWaitset()
{
	for (UDDSEntity* Entity : m_pEntities)
	{
		AttachEntityToWaitset(Entity);
	}
};
	
void MRSThreadedExecutor::AttachEntityToWaitset(UDDSEntity* Entity)
{
	if (!Entity)
		return;

	dds_attach_t EntityID = Entity->GetEntity();

	if (!AttachedEntities.Contains(EntityID))
	{
		dds_waitset_attach(WaitsetHandler, EntityID, EntityID);
		AttachedEntities.Add(EntityID);
	}
}

void MRSThreadedExecutor::DetachEntityFromWaitset(UDDSEntity* Entity)
{
	if (!Entity)
		return;

	dds_attach_t EntityID = Entity->GetEntity();

	if (AttachedEntities.Contains(EntityID))
	{
		dds_waitset_detach(WaitsetHandler, EntityID);
		AttachedEntities.Remove(EntityID);
	}
}

void MRSThreadedExecutor::DetachAllEntitiesFromWaitset()
{
	for (dds_attach_t EntityID : AttachedEntities)
	{
		dds_waitset_detach(WaitsetHandler, EntityID);
	}
	AttachedEntities.Empty();
};
