// Fill out your copyright notice in the Description page of Project Settings.


#include "Topic/DDSTopic.h"
#include "QoS/DDSQoS.h"
#include "Utils/MRSLogs.h"

UDDSTopic::UDDSTopic(const FObjectInitializer& Initializer)
{
    m_Type = EEntityType::TOPIC;
}

void UDDSTopic::Init()
{
    //TODO : To Delete ros prefix
    if (m_QosInfo.bUseRosPrefix)
    {
        FString Prefix = TEXT("");
        m_Name = Prefix.Append(m_Name);
    };

    if (!IsValid(m_OwnerParticipant))
    {
        m_State = EEntityState::NOT_INITIALIZED;
        return;
    }

    if (!IsValid(m_TopicProxy))
    {
        m_State = EEntityState::NOT_INITIALIZED;
        return;
    };    

    dds_qos_t* Qos = dds_create_qos();

    QoSUtils::SetQos(m_QosInfo, *Qos);

    m_Entity = dds_create_topic
    (
        m_OwnerParticipant->GetEntity(),
        m_TopicProxy->GetTypeDesc(),
        StringCast<ANSICHAR>(*m_Name).Get(),
        Qos,
        NULL
    );

    RC_DDS_CHECK(m_Entity); //DDS Check return code
    
    dds_delete_qos(Qos);

    m_State = EEntityState::INITIALIZED;
};

void UDDSTopic::Fini()
{
    RC_DDS_CHECK(dds_delete(m_Entity));  //DDS Check return code
    m_TopicProxy->Terminate();
};

void UDDSTopic::SetMessageType(TSubclassOf<UTopicProxy> MsgClass)
{
    if (MsgClass)
    {
        UTopicProxy* NewMsgObject = NewObject<UTopicProxy>(this, MsgClass);
        
        if (NewMsgObject)
        {
            m_TopicProxy = NewMsgObject;
            m_TopicProxy->Initialize();
        }
        else
        {
            UE_LOGFMT(LogMorse, Warning, "Can't create new message base on the specified Class.");
        }
    }
    else
    {
        UE_LOGFMT(LogMorse, Warning, "MsgClass is not valid");
    };
};

