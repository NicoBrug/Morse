#include "API/MorseBlueprintLib.h"
#include "Core/MorseEngineSubsystem.h"
#include "Utils/MRSLogs.h"

bool UMorseLib::CreateWriter(
    UObject* Owner,
    FTopicDescription Settings,
    TSubclassOf<UTopicProxy> DataType,
    UTopicProxy*& OutTopicProxy,
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
        pTopic->SetMessageType(DataType);
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

    UTopicProxy* dp = pTopic->GetTopicProxy();
    OutTopicProxy = dp;
    OutWriter = Writer;    

    UE_LOGFMT(LogMorse, Log, "Create Writer");

    return true;
}

bool UMorseLib::CreateReader(
    UObject* Owner,
    FTopicDescription Settings,
    TSubclassOf<UTopicProxy> DataType,
    UTopicProxy*& OutTopicProxy,
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

    OutTopicProxy = pTopic->GetTopicProxy();
    OutReader = Reader;

    UE_LOGFMT(LogMorse, Log, "Create Reader");
    return true;
};

