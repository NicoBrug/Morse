#include "PrimitiveTestDDS.h"

// Define macros for expected values
#define RESULT_PRIMITIVE_BOOL         true
#define RESULT_PRIMITIVE_BYTEVALUE    'A'
#define RESULT_PRIMITIVE_CHARVALUE    65
#define RESULT_PRIMITIVE_FLOAT32      420.20f
#define RESULT_PRIMITIVE_FLOAT64      123456.789
#define RESULT_PRIMITIVE_INT8         -128
#define RESULT_PRIMITIVE_UINT8        255
#define RESULT_PRIMITIVE_INT16        -32768
#define RESULT_PRIMITIVE_UINT16       65535
#define RESULT_PRIMITIVE_INT32        -2147483647
#define RESULT_PRIMITIVE_UINT32       4294967295u
#define RESULT_PRIMITIVE_INT64        -9223372036854775807ll
#define RESULT_PRIMITIVE_UINT64       18446744073709551615ull
#define RESULT_PRIMITIVE_STRING       FString("Hello World!")

BEGIN_DEFINE_SPEC(IDLPrimitiveSpec, "Morse.IDLPrimitive", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
UPrimitives_TopicProxy* TopicProxyWriter = nullptr;
UTopicProxy* TopicProxyBaseWriter = nullptr;
UDDSWriter* Writer = nullptr;

UPrimitives_TopicProxy* TopicProxyReader = nullptr;
UTopicProxy* TopicProxyBaseReader = nullptr;
UDDSReader* Reader = nullptr;
END_DEFINE_SPEC(IDLPrimitiveSpec)

void IDLPrimitiveSpec::Define()
{
	BeforeEach([this]
	{
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

		UMorseLib::CreateWriter(Owner, TopicSettings, UPrimitives_TopicProxy::StaticClass(), TopicProxyBaseWriter, Writer);
		TopicProxyWriter = Cast<UPrimitives_TopicProxy>(TopicProxyBaseWriter);

		UMorseLib::CreateReader(Owner, TopicSettings, UPrimitives_TopicProxy::StaticClass(), TopicProxyBaseReader, Reader);
		TopicProxyReader = Cast<UPrimitives_TopicProxy>(TopicProxyBaseReader);
		
		FROSPrimitives DataToWrite;
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
	

	It("Read Bool", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FROSPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);

		TestEqual("BoolValue should match", DataRead.BoolValue, RESULT_PRIMITIVE_BOOL);
	});

	It("Read Byte", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FROSPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);

		TestEqual("ByteValue should match", DataRead.ByteValue, RESULT_PRIMITIVE_BYTEVALUE);
	});

	It("Read Float32", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FROSPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);

		TestEqual("Float32Value should match", DataRead.Float32Value, RESULT_PRIMITIVE_FLOAT32);
	});

	It("Read Float64", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FROSPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);

		TestEqual("Float64Value should match", DataRead.Float64Value, RESULT_PRIMITIVE_FLOAT64);
	});

	It("Read Int8", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FROSPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);

		TestEqual("Int8Value should match", DataRead.Int8Value, RESULT_PRIMITIVE_INT8);
	});

	It("Read Int16", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FROSPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);
		
		TestEqual("Int16Value should match", DataRead.Int16Value, RESULT_PRIMITIVE_INT16);
	});

	It("Read UInt16", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FROSPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);
			
		TestEqual("Uint16Value should match", DataRead.Uint16Value, RESULT_PRIMITIVE_UINT16);
	});

	It("Read Int32", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FROSPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);
				
		TestEqual("Int32Value should match", DataRead.Int32Value, RESULT_PRIMITIVE_INT32);
	});

	It("Read UInt32", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FROSPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);
					
		TestEqual("Uint32Value should match", DataRead.Uint32Value, RESULT_PRIMITIVE_UINT32);
	});

	It("Read Int64", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FROSPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);
						
		TestEqual("Int64Value should match", DataRead.Int64Value, RESULT_PRIMITIVE_INT64);
	});
	
	It("Read UInt64", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FROSPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);
							
		TestEqual("Uint64Value should match", DataRead.Uint64Value, RESULT_PRIMITIVE_UINT64);
	});

	It("Read String", EAsyncExecution::TaskGraphMainThread, [this]()
	{
		Reader->Read();
		FROSPrimitives DataRead;
		TopicProxyReader->GetData(DataRead);
								
		TestEqual("StringValue should match", DataRead.StringValue, RESULT_PRIMITIVE_STRING);
	});
};
