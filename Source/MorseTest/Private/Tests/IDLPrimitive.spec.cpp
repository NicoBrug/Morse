#include "Tests/IDLPrimitive.spec.h"
#include "IDLPrimitives.h"
#include "DDS/Entity/DDSWriter.h"
#include "DDS/Entity/DDSReader.h"
#include "DDS/Entity/DDSTopic.h"
#include "API/MorseBlueprintLib.h"
#include "Core/MRSSubsystem.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"

BEGIN_DEFINE_SPEC(IDLPrimitiveSpec, "Morse.IDLPrimitive", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
UPrimitives_TopicProxy* TopicProxyWriter = nullptr;
UTopicProxy* TopicProxyBaseWriter = nullptr;
UDDSWriter* Writer = nullptr;
UPrimitives_TopicProxy* TopicProxyReader = nullptr;
UTopicProxy* TopicProxyBaseReader = nullptr;
UDDSReader* Reader = nullptr;
UWorld* World;
END_DEFINE_SPEC(IDLPrimitiveSpec)

static UWorld* GetWorld()
{
	if (GEngine)
	{
		if (FWorldContext* WorldContext = GEngine->GetWorldContextFromPIEInstance(0))
		{
			return WorldContext->World();
		}
	}
	return nullptr;
}

void IDLPrimitiveSpec::Define()
{
	BeforeEach([this]
	{
		AutomationOpenMap("/Engine/Maps/Entry");
		
		World = GetWorld();
		TestNotNull("Check if World is properly created", World);
		
		FQoSInfo QOS_TIME = FQoSInfo{
         FQoSDurability{EQosDurability::VOLATILE, 1},                     
         FQoSHistory{EQosHistory::KEEP_ALL, 0},                          
         FQoSReliability{EQosReliability::RELIABLE, 0},               
         FQoSLiveness{EQosLiveness::MANUAL_BY_TOPIC, 1000000000},        
         FQoSOwnership{EQosOwnership::SYSTEM_DEFAULT, 1},
         FQoSConsistency{EQosConsistency::SYSTEM_DEFAULT, false, false, false, false}
		};

		FTopicDescription TopicSettings;
		TopicSettings.SetName("TestTopic");
		TopicSettings.SetQualityOfService(QOS_TIME);

		UObject* Owner = GetTransientPackage();

		UMorseLib::CreateWriter(Owner, TopicSettings, UPrimitives_TopicProxy::StaticClass(), Writer);
		TopicProxyWriter = Writer->GetTopicProxy<UPrimitives_TopicProxy>();

		UMorseLib::CreateReader(Owner, TopicSettings, UPrimitives_TopicProxy::StaticClass(), Reader);
		TopicProxyReader = Reader->GetTopicProxy<UPrimitives_TopicProxy>();
		
		FIDLPrimitives DataToWrite;
		DataToWrite.BoolValue = RESULT_PRIMITIVE_BOOL;
		DataToWrite.ByteValue = RESULT_PRIMITIVE_BYTEVALUE;
		DataToWrite.CharValue = RESULT_PRIMITIVE_CHARVALUE;
		DataToWrite.Float32Value = RESULT_PRIMITIVE_FLOAT32;
		DataToWrite.Float64Value = RESULT_PRIMITIVE_FLOAT64;
		DataToWrite.Int8Value = RESULT_PRIMITIVE_INT8;
		//DataToWrite.Uint8Value = RESULT_PRIMITIVE_UINT8;
		DataToWrite.Int16Value = RESULT_PRIMITIVE_INT16;
		DataToWrite.Uint16Value = RESULT_PRIMITIVE_UINT16;
		DataToWrite.Int32Value = RESULT_PRIMITIVE_INT32;
		DataToWrite.Uint32Value = RESULT_PRIMITIVE_UINT32;
		DataToWrite.Int64Value = RESULT_PRIMITIVE_INT64;
		DataToWrite.Uint64Value = RESULT_PRIMITIVE_UINT64;
		DataToWrite.StringValue = RESULT_PRIMITIVE_STRING;
		
		TopicProxyWriter->SetData(DataToWrite);
		Writer->Write();
	});

	AfterEach([this]()
	{
		// Tear down the world and the actor
		if(Writer)
		 	Writer->Terminate();
		
		if(Reader)
		 	Reader->Terminate();
	});

	It("Should Read Byte", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);

		TestEqual("ByteValue should match", DataRead.ByteValue, RESULT_PRIMITIVE_BYTEVALUE);
	});

	It("Should Read Bool", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);

		TestEqual("BoolValue should match", DataRead.BoolValue, RESULT_PRIMITIVE_BOOL);
	});
	
	It("Should Read Float32", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);

		TestEqual("Float32Value should match", DataRead.Float32Value, RESULT_PRIMITIVE_FLOAT32);
	});

	It("Should Read Float64", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);

		TestEqual("Float64Value should match", DataRead.Float64Value, RESULT_PRIMITIVE_FLOAT64);
	});

	It("Should Read Int8", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);

		TestEqual("Int8Value should match", DataRead.Int8Value, RESULT_PRIMITIVE_INT8);
	});

	It("Should Read Int16", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);
		
		TestEqual("Int16Value should match", DataRead.Int16Value, RESULT_PRIMITIVE_INT16);
	});

	It("Should Read UInt16", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);
			
		TestEqual("Uint16Value should match", DataRead.Uint16Value, RESULT_PRIMITIVE_UINT16);
	});

	It("Should Read Int32", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);
				
		TestEqual("Int32Value should match", DataRead.Int32Value, RESULT_PRIMITIVE_INT32);
	});

	It("Should Read UInt32", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);
					
		TestEqual("Uint32Value should match", DataRead.Uint32Value, RESULT_PRIMITIVE_UINT32);
	});

	It("Should Read Int64", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);
						
		TestEqual("Int64Value should match", DataRead.Int64Value, RESULT_PRIMITIVE_INT64);
	});
	
	It("Should Read UInt64", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);
							
		TestEqual("Uint64Value should match", DataRead.Uint64Value, RESULT_PRIMITIVE_UINT64);
	});

	It("Should Read String", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);
								
		TestEqual("StringValue should match", DataRead.StringValue, RESULT_PRIMITIVE_STRING);
	});
};
