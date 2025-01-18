#include "DDS/Entity/DDSParticipant.h"

#include "XmlFile.h"
#include "Core/MRSSettings.h"
#include "DDS/Entity/DDSDomain.h"
#include "Utils/MRSLogs.h"

UDDSParticipant::UDDSParticipant(const FObjectInitializer& Initializer)
{

};

void UDDSParticipant::Initialize()
{
	Domain = new FDDSDomain();
	Domain->Initialize();
	dds_domainid_t Domani = 0;
	EntityHandler = dds_create_participant
	(
		Domain->GetDomainId(), 
		NULL, 
		NULL
	);
		
	RC_DDS_CHECK(EntityHandler); //DDS Check return code
	
	if (EntityHandler < 0)
	{
		SetState(EEntityState::NOT_INITIALIZED);
		return;
	};

	SetState(EEntityState::INITIALIZED);
};

void UDDSParticipant::Terminate()
{
	UE_LOG(LogMorse, Log, TEXT("Participant Terminated"));
	
	RC_DDS_CHECK(dds_delete(EntityHandler)); //When participant is deleted, all this children is deleted also (all reader/writer etc)

	if(Domain)
	{
		Domain->Terminate();
	};
	
	SetState(EEntityState::DESTROYED);
};

