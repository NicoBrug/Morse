#include "API/MorseBlueprintLib.h"
#include "Core/MorseEngineSubsystem.h"
#include "Utils/MRSLogs.h"

bool UMorseLib::CreateWriterBlueprint(
    UObject* Owner,
    FTopicDescription Settings,
    TSubclassOf<UTopicProxy> DataType,
    UTopicProxy*& OutTopicProxy,
    UDDSWriter*& OutWriter)
{
    bool Res = UMorseLib::CreateWriter(Owner, Settings, DataType, OutWriter);

    if(Res != true || !OutWriter || !OutWriter->GetTopic())
        return false;
    
    OutTopicProxy = OutWriter->GetTopic()->GetTopicProxy();
    return true;
};

bool UMorseLib::CreateReaderBlueprint(
    UObject* Owner,
    FTopicDescription Settings,
    TSubclassOf<UTopicProxy> DataType,
    UTopicProxy*& OutTopicProxy,
    UDDSReader*& OutReader)
{

    bool Res = UMorseLib::CreateReader(Owner, Settings, DataType, OutReader);

    if(Res != true || !OutReader || !OutReader->GetTopic())
        return false;
    
    OutTopicProxy = OutReader->GetTopic()->GetTopicProxy();
    return true;
};

bool UMorseLib::CreateReader(UObject* Owner, FTopicDescription Settings, TSubclassOf<UTopicProxy> DataType,
    UDDSReader*& OutReader)
{
    if (!Owner)
    {
        UE_LOGFMT(LogMorse, Warning, "CreateReader : No Valid Owner");
        return false;
    };

    UMorseEngineSubsystem* Morse = UMorseEngineSubsystem::Get();

    UDDSTopic* pTopic = NewObject<UDDSTopic>(Owner);
    if (pTopic)
    {
        pTopic->SetName(Settings.Name);
        pTopic->SetMessageType(DataType); //TODO : Change function name and call in UTopic Initialisation 
        pTopic->SetParticipant(Morse->GetDefaultParticipant());
        pTopic->SetQoS(Settings.QualityOfService);
        pTopic->Initialize();
    }

    UDDSReader* Reader = NewObject<UDDSReader>(Owner);

    if (Reader)
    {
        Reader->SetTopic(pTopic);
        Reader->SetParticipant(Morse->GetDefaultParticipant());
        Reader->SetQoS(Settings.QualityOfService);
        Reader->Initialize();
    };

    OutReader = Reader;
    UE_LOGFMT(LogMorse, Log, "Create Reader -> Topic  {0} | DataType {1}", Settings.Name, *DataType->GetName());
    return true;
};

bool UMorseLib::CreateWriter(UObject* Owner, FTopicDescription Settings, TSubclassOf<UTopicProxy> DataType,
    UDDSWriter*& OutWriter)
{
    if (!Owner)
    {
        UE_LOGFMT(LogMorse, Warning, "CreateWriter : No Valid Owner");
        return false;
    };

    UMorseEngineSubsystem* Morse = UMorseEngineSubsystem::Get();

    UDDSTopic* pTopic = NewObject<UDDSTopic>(Owner);

    if (pTopic)
    {
        pTopic->SetName(Settings.Name);
        pTopic->SetMessageType(DataType); //TODO : Change function name and call in UTopic Initialisation 
        pTopic->SetParticipant(Morse->GetDefaultParticipant());
        pTopic->SetQoS(Settings.QualityOfService);
        pTopic->Initialize();
    };

    UDDSWriter* Writer = NewObject<UDDSWriter>(Owner);
    if (Writer)
    {
        Writer->SetTopic(pTopic);
        Writer->SetParticipant(Morse->GetDefaultParticipant());
        Writer->SetQoS(Settings.QualityOfService);
        Writer->Initialize();
    };

    OutWriter = Writer;    

    UE_LOGFMT(LogMorse, Log, "Create Writer -> Topic  {0} | DataType {1}", Settings.Name, *DataType->GetName());
    return true;
};
