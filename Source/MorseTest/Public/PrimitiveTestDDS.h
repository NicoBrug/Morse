#pragma once

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "ROSPrimitives.h"
#include "Topic/DDSWriter.h"
#include "Topic/DDSReader.h"
#include "Topic/DDSTopic.h"
#include "API/MorseBlueprintLib.h"
#include "Core/MorseEngineSubsystem.h"


	 
// Remplacez par une catégorie appropriée pour votre projet
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDDSTopicTest, "Project.DDSTopicTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::EngineFilter)

//
//
//
// bool FDDSTopicTest::RunTest(const FString& Parameters)
// {
//     // 1. Configuration du QoS et des paramètres du topic
//     FQoSInfo QOS_TIME = FQoSInfo{
//         FQoSDurability{EQosDurability::VOLATILE, 1},                     
//         FQoSHistory{EQosHistory::KEEP_ALL, 0},                          
//         FQoSReliability{EQosReliability::RELIABLE, 0},               
//         FQoSLiveness{EQosLiveness::MANUAL_BY_TOPIC, 1000000000},        
//         FQoSOwnership{EQosOwnership::SYSTEM_DEFAULT, 1},
//         FQoSConsistency{EQosConsistency::SYSTEM_DEFAULT, false, false, false, false}
//     };
//
//     FTopicDescription TopicSettings;
//     TopicSettings.SetName("TestTopic");
//     TopicSettings.SetQualityOfService(QOS_TIME);
//
//     // 2. Création d'un Writer
//     UObject* Owner = GetTransientPackage();
//
//     UPrimitives_TopicProxy* TopicProxyWriter = nullptr;
//     UTopicProxy* TopicProxyBaseWriter = nullptr;
//     UDDSWriter* Writer = nullptr;
//     
//     UMorseLib::CreateWriter(Owner, TopicSettings, UPrimitives_TopicProxy::StaticClass(), TopicProxyBaseWriter, Writer);
//     TopicProxyWriter = Cast<UPrimitives_TopicProxy>(TopicProxyBaseWriter);
//         
//     TestNotNull("Writer should be created", Writer);
//     TestNotNull("Topic Proxy for Writer should be created",TopicProxyWriter);
//     
//     // 3. Mise à jour des données dans le Writer
//     FROSPrimitives DataToWrite;
//     DataToWrite.BoolValue = true;
//     DataToWrite.Float32Value = 42.42f;
//     DataToWrite.StringValue = "Test String";
//
//     TopicProxyWriter->SetData(DataToWrite);
//     Writer->Write();
//
//     // 4. Création d'un Reader
//     UPrimitives_TopicProxy* TopicProxyReader = nullptr;
//     UTopicProxy* TopicProxyBaseReader = nullptr;
//     UDDSReader* Reader = nullptr;
//     UMorseLib::CreateReader(Owner, TopicSettings, UPrimitives_TopicProxy::StaticClass(), TopicProxyBaseReader, Reader);
//     TopicProxyReader = Cast<UPrimitives_TopicProxy>(TopicProxyBaseReader);
//
//     TestNotNull("Reader should be created", Reader);
//     TestNotNull("Topic Proxy for Reader should be created",TopicProxyReader);
//
//     // 5. Lecture des données depuis le Reader
//     Reader->Read();
//
//     // 6. Validation des données lues
//     FROSPrimitives DataRead;
//     TopicProxyReader->GetData(DataRead);
//
//     TestEqual("BoolValue should match", DataRead.BoolValue, DataToWrite.BoolValue);
//     TestEqual("Float32Value should match", DataRead.Float32Value, DataToWrite.Float32Value);
//     TestEqual("StringValue should match", DataRead.StringValue, DataToWrite.StringValue);
//
//     return true; // Si toutes les assertions passent
// }
