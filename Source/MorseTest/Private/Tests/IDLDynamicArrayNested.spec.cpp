#include "Tests/IDLDynamicArrayNested.spec.h"

#include "IDLDynamicArrayNested.h"
#include "API/MorseBlueprintLib.h"
#include "Core/MRSSubsystem.h"
#include "DDS/Entity/DDSReader.h"
#include "DDS/Entity/DDSWriter.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "Tests/IDLPrimitive.spec.h"

BEGIN_DEFINE_SPEC(IDLDynamicArrayNestedSpec, "Morse.IDLDynamicArrayNested", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
UDynamicArrayNested_TopicProxy* TopicProxyWriter = nullptr;
UTopicProxy* TopicProxyBaseWriter = nullptr;
UDDSWriter* Writer = nullptr;
UDynamicArrayNested_TopicProxy* TopicProxyReader = nullptr;
UTopicProxy* TopicProxyBaseReader = nullptr;
UDDSReader* Reader = nullptr;
UWorld* World;
END_DEFINE_SPEC(IDLDynamicArrayNestedSpec)

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

void IDLDynamicArrayNestedSpec::Define()
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

		UMorseLib::CreateWriter(Owner, TopicSettings, UDynamicArrayNested_TopicProxy::StaticClass(), Writer);
		TopicProxyWriter = Writer->GetTopicProxy<UDynamicArrayNested_TopicProxy>();

		UMorseLib::CreateReader(Owner, TopicSettings, UDynamicArrayNested_TopicProxy::StaticClass(), Reader);
		TopicProxyReader = Reader->GetTopicProxy<UDynamicArrayNested_TopicProxy>();

		
		FIDLDynamicArrayNested DataToWrite;
		DataToWrite.PrimitiveValues = RESULT_DYNAMIC_NESTED_PRIMITIVES;
		
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
	
	// Test de lecture des BoolValues
	It("Should Read BoolValues from PrimitiveValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayNested DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("PrimitiveValues[0].BoolValue should match", DataRead.PrimitiveValues[0].BoolValue, RESULT_PRIMITIVE_BOOL_1);
	    TestEqual("PrimitiveValues[1].BoolValue should match", DataRead.PrimitiveValues[1].BoolValue, RESULT_PRIMITIVE_BOOL_2);
	});

	// Test de lecture des ByteValues
	It("Should Read ByteValues from PrimitiveValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayNested DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("PrimitiveValues[0].ByteValue should match", DataRead.PrimitiveValues[0].ByteValue, RESULT_PRIMITIVE_BYTE_1);
	    TestEqual("PrimitiveValues[1].ByteValue should match", DataRead.PrimitiveValues[1].ByteValue, RESULT_PRIMITIVE_BYTE_2);
	});

	// Test de lecture des CharValues
	It("Should Read CharValues from PrimitiveValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayNested DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("PrimitiveValues[0].CharValue should match", DataRead.PrimitiveValues[0].CharValue, RESULT_PRIMITIVE_CHAR_1);
	    TestEqual("PrimitiveValues[1].CharValue should match", DataRead.PrimitiveValues[1].CharValue, RESULT_PRIMITIVE_CHAR_2);
	});

	// Test de lecture des Float32Values
	It("Should Read Float32Values from PrimitiveValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayNested DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("PrimitiveValues[0].Float32Value should match", DataRead.PrimitiveValues[0].Float32Value, RESULT_PRIMITIVE_FLOAT32_1);
	    TestEqual("PrimitiveValues[1].Float32Value should match", DataRead.PrimitiveValues[1].Float32Value, RESULT_PRIMITIVE_FLOAT32_2);
	});

	// Test de lecture des Float64Values
	It("Should Read Float64Values from PrimitiveValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayNested DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("PrimitiveValues[0].Float64Value should match", DataRead.PrimitiveValues[0].Float64Value, RESULT_PRIMITIVE_FLOAT64_1);
	    TestEqual("PrimitiveValues[1].Float64Value should match", DataRead.PrimitiveValues[1].Float64Value, RESULT_PRIMITIVE_FLOAT64_2);
	});

	// Test de lecture des Int8Values
	It("Should Read Int8Values from PrimitiveValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayNested DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("PrimitiveValues[0].Int8Value should match", DataRead.PrimitiveValues[0].Int8Value, RESULT_PRIMITIVE_INT8_1);
	    TestEqual("PrimitiveValues[1].Int8Value should match", DataRead.PrimitiveValues[1].Int8Value, RESULT_PRIMITIVE_INT8_2);
	});

	// Test de lecture des UInt8Values
	It("Should Read UInt8Values from PrimitiveValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayNested DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("PrimitiveValues[0].UInt8Value should match", DataRead.PrimitiveValues[0].Uint8Value, RESULT_PRIMITIVE_UINT8_1);
	    TestEqual("PrimitiveValues[1].UInt8Value should match", DataRead.PrimitiveValues[1].Uint8Value, RESULT_PRIMITIVE_UINT8_2);
	});

	// Test de lecture des Int16Values
	It("Should Read Int16Values from PrimitiveValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayNested DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("PrimitiveValues[0].Int16Value should match", DataRead.PrimitiveValues[0].Int16Value, RESULT_PRIMITIVE_INT16_1);
	    TestEqual("PrimitiveValues[1].Int16Value should match", DataRead.PrimitiveValues[1].Int16Value, RESULT_PRIMITIVE_INT16_2);
	});

	// Test de lecture des UInt16Values
	It("Should Read UInt16Values from PrimitiveValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayNested DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("PrimitiveValues[0].UInt16Value should match", DataRead.PrimitiveValues[0].Uint16Value, RESULT_PRIMITIVE_UINT16_1);
	    TestEqual("PrimitiveValues[1].UInt16Value should match", DataRead.PrimitiveValues[1].Uint16Value, RESULT_PRIMITIVE_UINT16_2);
	});

	// Test de lecture des Int32Values
	It("Should Read Int32Values from PrimitiveValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayNested DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("PrimitiveValues[0].Int32Value should match", DataRead.PrimitiveValues[0].Int32Value, RESULT_PRIMITIVE_INT32_1);
	    TestEqual("PrimitiveValues[1].Int32Value should match", DataRead.PrimitiveValues[1].Int32Value, RESULT_PRIMITIVE_INT32_2);
	});

	// Test de lecture des UInt32Values
	It("Should Read UInt32Values from PrimitiveValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayNested DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("PrimitiveValues[0].UInt32Value should match", DataRead.PrimitiveValues[0].Uint32Value, RESULT_PRIMITIVE_UINT32_1);
	    TestEqual("PrimitiveValues[1].UInt32Value should match", DataRead.PrimitiveValues[1].Uint32Value, RESULT_PRIMITIVE_UINT32_2);
	});

	// Test de lecture des Int64Values
	It("Should Read Int64Values from PrimitiveValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayNested DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("PrimitiveValues[0].Int64Value should match", DataRead.PrimitiveValues[0].Int64Value, RESULT_PRIMITIVE_INT64_1);
	    TestEqual("PrimitiveValues[1].Int64Value should match", DataRead.PrimitiveValues[1].Int64Value, RESULT_PRIMITIVE_INT64_2);
	});

	// Test de lecture des UInt64Values
	It("Should Read UInt64Values from PrimitiveValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayNested DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("PrimitiveValues[0].UInt64Value should match", DataRead.PrimitiveValues[0].Uint64Value, RESULT_PRIMITIVE_UINT64_1);
	    TestEqual("PrimitiveValues[1].UInt64Value should match", DataRead.PrimitiveValues[1].Uint64Value, RESULT_PRIMITIVE_UINT64_2);
	});

	// Test de lecture des StringValues
	It("Should Read StringValues from PrimitiveValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayNested DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("PrimitiveValues[0].StringValue should match", DataRead.PrimitiveValues[0].StringValue, RESULT_PRIMITIVE_STRING_1);
	    TestEqual("PrimitiveValues[1].StringValue should match", DataRead.PrimitiveValues[1].StringValue, RESULT_PRIMITIVE_STRING_2);
	});
};	
