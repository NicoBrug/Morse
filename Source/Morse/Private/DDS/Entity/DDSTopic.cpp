#include "DDS/Entity/DDSTopic.h"
#include "DDS/QoS/DDSQoS.h"
#include "Utils/MRSLogs.h"

UDDSTopic::UDDSTopic(const FObjectInitializer& Initializer)
{
    SetType(EEntityType::DDS_TOPIC);
}

void UDDSTopic::Initialize()
{
    if (!IsValid(OwnerParticipant))
    {
        SetState(EEntityState::NOT_INITIALIZED);
        return;
    }

    if (!IsValid(TopicProxy))
    {
        SetState(EEntityState::NOT_INITIALIZED);
        return;
    };    

    dds_qos_t* Qos = dds_create_qos();

    QoSUtils::SetQos(GetQoS(), *Qos);

    EntityHandler = dds_create_topic
    (
        OwnerParticipant->GetEntity(),
        TopicProxy->GetTypeDesc(),
        StringCast<ANSICHAR>(*TopicName).Get(),
        Qos,
        NULL
    );

    RC_DDS_CHECK(EntityHandler); //DDS Check return code
    
    dds_delete_qos(Qos);

    SetState(EEntityState::INITIALIZED);
};

void UDDSTopic::Terminate()
{
    RC_DDS_CHECK(dds_delete(EntityHandler));  //DDS Check return code
    TopicProxy->Terminate();
    SetState(EEntityState::DESTROYED);
};

void UDDSTopic::SetMessageType(TSubclassOf<UTopicProxy> MsgClass)
{
    if (MsgClass)
    {
        UTopicProxy* NewMsgObject = NewObject<UTopicProxy>(this, MsgClass);
        
        if (NewMsgObject)
        {
            TopicProxy = NewMsgObject;
            TopicProxy->Initialize();
        }
        else
        {
            UE_LOGFMT(LogMorse, Warning, "Can't create new message base on the specified Class.");
        };
    }
    else
    {
        UE_LOGFMT(LogMorse, Warning, "MsgClass is not valid");
    };
};

