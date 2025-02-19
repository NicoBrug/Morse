#include "Actors/MRSActorState.h"
#include "MorseDataModel/Public/Utils/MorseDataModelUtils.h"




void FMRSActorState::DDSToUE(const Unreal_Actor_ActorState& InData)
{
        UMorseDataModelUtils::DDSStringToUE(InData.Name, Name);
        UMorseDataModelUtils::DDSStringToUE(InData.Id, Id);
        UMorseDataModelUtils::DDSTransformToUE(InData.Transform, Transform);
};

void FMRSActorState::UEToDDS(Unreal_Actor_ActorState& OutData) 
{
        UMorseDataModelUtils::UEStringToDDS(Name, OutData.Name);
        UMorseDataModelUtils::UEStringToDDS(Id, OutData.Id);
        UMorseDataModelUtils::UETransformToDDS(Transform, OutData.Transform);
};

void UActorState_TopicProxy::Initialize()
{
    Data = Unreal_Actor_ActorState__alloc();
};

void UActorState_TopicProxy::Terminate()
{
    Unreal_Actor_ActorState_free(Data, DDS_FREE_ALL);
};

const dds_topic_descriptor_t* UActorState_TopicProxy::GetTypeDesc()
{
     return &Unreal_Actor_ActorState_desc;
};

void* UActorState_TopicProxy::Get()
{
    return Data;
};

void UActorState_TopicProxy::ExecuteMessageCallback()
{
    FMRSActorState NewData;
    NewData.DDSToUE(*Data);
    OnDataChanged.Broadcast(NewData);
};

void UActorState_TopicProxy::GetData(FMRSActorState& Output)
{
    Output.DDSToUE(*Data);
};

void UActorState_TopicProxy::SetData(FMRSActorState Input)
{
    Input.UEToDDS(*Data);
};



