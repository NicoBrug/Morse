#include "Tests/IDLNested.spec.h"

#include "IDLNested.h"
#include "IDLPrimitives.h"
#include "API/MorseBlueprintLib.h"
#include "Core/MRSSubsystem.h"
#include "DDS/Entity/DDSReader.h"
#include "DDS/Entity/DDSWriter.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "Tests/IDLPrimitive.spec.h"

BEGIN_DEFINE_SPEC(IDLNestedSpec, "Morse.IDLNested", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
UNested_TopicProxy* TopicProxyWriter = nullptr;
UTopicProxy* TopicProxyBaseWriter = nullptr;
UDDSWriter* Writer = nullptr;
UNested_TopicProxy* TopicProxyReader = nullptr;
UTopicProxy* TopicProxyBaseReader = nullptr;
UDDSReader* Reader = nullptr;
UWorld* World;
END_DEFINE_SPEC(IDLNestedSpec)

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

void IDLNestedSpec::Define()
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

		UMorseLib::CreateWriter(Owner, TopicSettings, UNested_TopicProxy::StaticClass(), Writer);
		TopicProxyWriter = Writer->GetTopicProxy<UNested_TopicProxy>();

		UMorseLib::CreateReader(Owner, TopicSettings, UNested_TopicProxy::StaticClass(), Reader);
		TopicProxyReader = Reader->GetTopicProxy<UNested_TopicProxy>();
				
		FIDLNested Nested;
		Nested.PrimitiveValues.BoolValue = RESULT_PRIMITIVE_BOOL;
		Nested.PrimitiveValues.ByteValue = RESULT_PRIMITIVE_BYTEVALUE;
		Nested.PrimitiveValues.CharValue = RESULT_PRIMITIVE_CHARVALUE;
		Nested.PrimitiveValues.Float32Value = RESULT_PRIMITIVE_FLOAT32;
		Nested.PrimitiveValues.Float64Value = RESULT_PRIMITIVE_FLOAT64;
		Nested.PrimitiveValues.Int8Value = RESULT_PRIMITIVE_INT8;
		//DataToWrite.Uint8Value = RESULT_PRIMITIVE_UINT8;
		Nested.PrimitiveValues.Int16Value = RESULT_PRIMITIVE_INT16;
		Nested.PrimitiveValues.Uint16Value = RESULT_PRIMITIVE_UINT16;
		Nested.PrimitiveValues.Int32Value = RESULT_PRIMITIVE_INT32;
		Nested.PrimitiveValues.Uint32Value = RESULT_PRIMITIVE_UINT32;
		Nested.PrimitiveValues.Int64Value = RESULT_PRIMITIVE_INT64;
		Nested.PrimitiveValues.Uint64Value = RESULT_PRIMITIVE_UINT64;
		Nested.PrimitiveValues.StringValue = RESULT_PRIMITIVE_STRING;
		
		TopicProxyWriter->SetData(Nested);
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
		FIDLNested DataRead;
		TopicProxyReader->GetData(DataRead);

		TestEqual("ByteValue should match", DataRead.PrimitiveValues.ByteValue, RESULT_PRIMITIVE_BYTEVALUE);
	});

	It("Should Read Nested Bool", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLNested DataRead;
		TopicProxyReader->GetData(DataRead);

		TestEqual("BoolValue should match", DataRead.PrimitiveValues.BoolValue, RESULT_PRIMITIVE_BOOL);
	});
	
	It("Should Read Nested Float32", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLNested DataRead;
		TopicProxyReader->GetData(DataRead);

		TestEqual("Float32Value should match", DataRead.PrimitiveValues.Float32Value, RESULT_PRIMITIVE_FLOAT32);
	});

	It("Should Read Nested Float64", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLNested DataRead;
		TopicProxyReader->GetData(DataRead);

		TestEqual("Float64Value should match", DataRead.PrimitiveValues.Float64Value, RESULT_PRIMITIVE_FLOAT64);
	});

	It("Should Read Nested Int8", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLNested DataRead;
		TopicProxyReader->GetData(DataRead);

		TestEqual("Int8Value should match", DataRead.PrimitiveValues.Int8Value, RESULT_PRIMITIVE_INT8);
	});

	It("Should Read Nested Int16", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLNested DataRead;
		TopicProxyReader->GetData(DataRead);
		
		TestEqual("Int16Value should match", DataRead.PrimitiveValues.Int16Value, RESULT_PRIMITIVE_INT16);
	});

	It("Should Read Nested UInt16", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLNested DataRead;
		TopicProxyReader->GetData(DataRead);
			
		TestEqual("Uint16Value should match", DataRead.PrimitiveValues.Uint16Value, RESULT_PRIMITIVE_UINT16);
	});

	It("Should Read Nested Int32", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLNested DataRead;
		TopicProxyReader->GetData(DataRead);
				
		TestEqual("Int32Value should match", DataRead.PrimitiveValues.Int32Value, RESULT_PRIMITIVE_INT32);
	});

	It("Should Read Nested UInt32", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLNested DataRead;
		TopicProxyReader->GetData(DataRead);
					
		TestEqual("Uint32Value should match", DataRead.PrimitiveValues.Uint32Value, RESULT_PRIMITIVE_UINT32);
	});

	It("Should Read Nested Int64", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLNested DataRead;
		TopicProxyReader->GetData(DataRead);
						
		TestEqual("Int64Value should match", DataRead.PrimitiveValues.Int64Value, RESULT_PRIMITIVE_INT64);
	});
	
	It("Should Read Nested UInt64", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLNested DataRead;
		TopicProxyReader->GetData(DataRead);
							
		TestEqual("Uint64Value should match", DataRead.PrimitiveValues.Uint64Value, RESULT_PRIMITIVE_UINT64);
	});

	It("Should Read Nested String", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FIDLNested DataRead;
		TopicProxyReader->GetData(DataRead);
								
		TestEqual("StringValue should match", DataRead.PrimitiveValues.StringValue, RESULT_PRIMITIVE_STRING);
	});
};