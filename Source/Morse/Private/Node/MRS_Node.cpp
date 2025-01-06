#include "Node/MRS_BaseNode.h"

UDDSTopic* UMRS_BaseNode::CreateTopic(FTopicDescription Params, FQoSInfo QoS)
{
    UDDSTopic* Topic = NewObject<UDDSTopic>(this);
    //if (Topic)
    //{
    //    Topic->SetName(Params.Name);
    //    Topic->SetMessageType(Params.DataType);
    //    Topic->SetParticipant(m_Participant);
    //    Topic->SetQoS(QoS);
    //    Topic->Init();
    //}
    return Topic;
}

UDDSWriter* UMRS_BaseNode::CreateWriter(UDDSTopic* Topic, FQoSInfo QoS)
{
    UDDSWriter* Writer = NewObject<UDDSWriter>(this);
    //if (Writer && Topic)
    //{
    //    Writer->SetTopic(Topic);
    //    Writer->SetParticipant(m_Participant);
    //    Writer->SetQoS(QoS);
    //    Writer->Init();
    //}
    return Writer;
}

UDDSReader* UMRS_BaseNode::CreateReader(UDDSTopic* Topic, FQoSInfo QoS)
{
    UDDSReader* Reader = NewObject<UDDSReader>(this);
    //if (Reader && Topic)
    //{
    //    Reader->SetTopic(Topic);
    //    Reader->SetParticipant(m_Participant);
    //    Reader->SetQoS(QoS);
    //    Reader->Init();
    //}
    return Reader;
}