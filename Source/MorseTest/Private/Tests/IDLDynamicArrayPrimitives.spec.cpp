#include "Tests/IDLDynamicArrayPrimitives.spec.h"

#include "IDLDynamicArrayPrimitives.h"
#include "API/MorseBlueprintLib.h"
#include "Core/MRSSubsystem.h"
#include "DDS/Entity/DDSReader.h"
#include "DDS/Entity/DDSWriter.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "Tests/IDLPrimitive.spec.h"

BEGIN_DEFINE_SPEC(IDLDynamicArrayPrimitivesSpec, "Morse.IDLDynamicArrayPrimitives", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
UDynamicArrayPrimitives_TopicProxy* TopicProxyWriter = nullptr;
UTopicProxy* TopicProxyBaseWriter = nullptr;
UDDSWriter* Writer = nullptr;
UDynamicArrayPrimitives_TopicProxy* TopicProxyReader = nullptr;
UTopicProxy* TopicProxyBaseReader = nullptr;
UDDSReader* Reader = nullptr;
UWorld* World;
END_DEFINE_SPEC(IDLDynamicArrayPrimitivesSpec)

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

void IDLDynamicArrayPrimitivesSpec::Define()
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

		UMorseLib::CreateWriter(Owner, TopicSettings, UDynamicArrayPrimitives_TopicProxy::StaticClass(), Writer);
		TopicProxyWriter = Writer->GetTopicProxy<UDynamicArrayPrimitives_TopicProxy>();

		UMorseLib::CreateReader(Owner, TopicSettings, UDynamicArrayPrimitives_TopicProxy::StaticClass(), Reader);
		TopicProxyReader = Reader->GetTopicProxy<UDynamicArrayPrimitives_TopicProxy>();
		
		FIDLDynamicArrayPrimitives DataToWrite;
		DataToWrite.BoolValues = RESULT_DYNAMIC_BOOL_VALUES;
		DataToWrite.ByteValues = RESULT_DYNAMIC_BYTE_VALUES;
		DataToWrite.CharValues = RESULT_DYNAMIC_CHAR_VALUES;
		DataToWrite.Float32Values = RESULT_DYNAMIC_FLOAT32_VALUES;
		DataToWrite.Float64Values = RESULT_DYNAMIC_FLOAT64_VALUES;
		DataToWrite.Int8Values = RESULT_DYNAMIC_INT8_VALUES;
		DataToWrite.Uint8Values = RESULT_DYNAMIC_UINT8_VALUES;
		DataToWrite.Int16Values = RESULT_DYNAMIC_INT16_VALUES;
		DataToWrite.Uint16Values = RESULT_DYNAMIC_UINT16_VALUES;
		DataToWrite.Int32Values = RESULT_DYNAMIC_INT32_VALUES;
		DataToWrite.Uint32Values = RESULT_DYNAMIC_UINT32_VALUES;
		DataToWrite.Int64Values = RESULT_DYNAMIC_INT64_VALUES;
		DataToWrite.Uint64Values = RESULT_DYNAMIC_UINT64_VALUES;
		DataToWrite.StringValues = RESULT_DYNAMIC_STRING_VALUES;
		
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

	It("Should Read BoolValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayPrimitives DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("BoolValues should match", DataRead.BoolValues, RESULT_DYNAMIC_BOOL_VALUES);
	});

	It("Should Read ByteValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayPrimitives DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("ByteValues should match", DataRead.ByteValues, RESULT_DYNAMIC_BYTE_VALUES);
	});

	It("Should Read CharValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayPrimitives DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("CharValues should match", DataRead.CharValues, RESULT_DYNAMIC_CHAR_VALUES);
	});

	It("Should Read Float32Values", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayPrimitives DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("Float32Values should match", DataRead.Float32Values, RESULT_DYNAMIC_FLOAT32_VALUES);
	});

	It("Should Read Float64Values", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayPrimitives DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("Float64Values should match", DataRead.Float64Values, RESULT_DYNAMIC_FLOAT64_VALUES);
	});

	It("Should Read Int8Values", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayPrimitives DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("Int8Values should match", DataRead.Int8Values, RESULT_DYNAMIC_INT8_VALUES);
	});

	It("Should Read Uint8Values", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayPrimitives DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("Uint8Values should match", DataRead.Uint8Values, RESULT_DYNAMIC_UINT8_VALUES);
	});

	It("Should Read Int16Values", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayPrimitives DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("Int16Values should match", DataRead.Int16Values, RESULT_DYNAMIC_INT16_VALUES);
	});

	It("Should Read Uint16Values", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayPrimitives DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("Uint16Values should match", DataRead.Uint16Values, RESULT_DYNAMIC_UINT16_VALUES);
	});

	It("Should Read Int32Values", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayPrimitives DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("Int32Values should match", DataRead.Int32Values, RESULT_DYNAMIC_INT32_VALUES);
	});

	It("Should Read Uint32Values", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayPrimitives DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("Uint32Values should match", DataRead.Uint32Values, RESULT_DYNAMIC_UINT32_VALUES);
	});

	It("Should Read Int64Values", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayPrimitives DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("Int64Values should match", DataRead.Int64Values, RESULT_DYNAMIC_INT64_VALUES);
	});

	It("Should Read Uint64Values", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayPrimitives DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("Uint64Values should match", DataRead.Uint64Values, RESULT_DYNAMIC_UINT64_VALUES);
	});

	It("Should Read StringValues", EAsyncExecution::TaskGraphMainThread, [this]()
	{
	    Reader->Read();
	    FIDLDynamicArrayPrimitives DataRead;
	    TopicProxyReader->GetData(DataRead);

	    TestEqual("StringValues should match", DataRead.StringValues, RESULT_DYNAMIC_STRING_VALUES);
	});

};