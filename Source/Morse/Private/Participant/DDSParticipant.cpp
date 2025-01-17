#include "Participant/DDSParticipant.h"

#include "XmlFile.h"
#include "Core/MorseSettings.h"
#include "Participant/DDSDomain.h"
#include "Utils/MRSLogs.h"

UDDSParticipant::UDDSParticipant(const FObjectInitializer& Initializer)
{

};

void UDDSParticipant::Initialize()
{
	Domain = new FDDSDomain();
	Domain->Initialize();
	
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
	if(Domain)
	{
		Domain->Terminate();
	};
	
	RC_DDS_CHECK(dds_delete(EntityHandler)); //DDS Check return code
	SetState(EEntityState::DESTROYED);
};

