#include "Exemple/MRSHelloWorld.h"

#include "Utils/MorseDataModelUtils.h"


void FMRSHelloWorld::DDSToUE(const Unreal_Exemple_HelloWorld& InData)
{
        UMorseDataModelUtils::DDSStringToUE(InData.HelloStr, Hellostr);
        Hellofloat = InData.HelloFloat;
};

void FMRSHelloWorld::UEToDDS(Unreal_Exemple_HelloWorld& OutData) 
{
        UMorseDataModelUtils::UEStringToDDS(Hellostr, OutData.HelloStr);
        OutData.HelloFloat = Hellofloat;
};

void UHelloWorld_TopicProxy::Initialize()
{
    Data = Unreal_Exemple_HelloWorld__alloc();
};

void UHelloWorld_TopicProxy::Terminate()
{
    Unreal_Exemple_HelloWorld_free(Data, DDS_FREE_ALL);
};

const dds_topic_descriptor_t* UHelloWorld_TopicProxy::GetTypeDesc()
{
     return &Unreal_Exemple_HelloWorld_desc;
};

void* UHelloWorld_TopicProxy::Get()
{
    return Data;
};

void UHelloWorld_TopicProxy::ExecuteMessageCallback()
{
    FMRSHelloWorld NewData;
    NewData.DDSToUE(*Data);
    OnDataChanged.Broadcast(NewData);
};

void UHelloWorld_TopicProxy::GetData(FMRSHelloWorld& Output)
{
    Output.DDSToUE(*Data);
};

void UHelloWorld_TopicProxy::SetData(FMRSHelloWorld Input)
{
    Input.UEToDDS(*Data);
};



