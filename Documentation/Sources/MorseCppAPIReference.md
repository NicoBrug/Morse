# Morse C++ API Reference

## Write Data
Add the include for DDS Writer
```
#include "Topic/DDSWriter.h" 
```
For create a DDS Writer, you need to setup the settings of the topic you want to write on. 
The Settings is contain in a struct called FTopicDescription. 
### Create Writer
```
TObjectPtr<UClock_TopicProxy> WriterTopicProxy;
UDDSWriter* Writer;

FTopicDescription Settings;
Settings.SetName("rt/clock");
Settings.SetQualityOfService(QOS_TIME);

UMorseLib::CreateWriter(this, Settings, UClock_TopicProxy::StaticClass(), Writer);

WriterTopicProxy = Writer->GetTopicProxy<UClock_TopicProxy>();
```
Operation of writing the data inside the topic proxy on DDS. Before that, you can modify the data inside the topic proxy. 
### Write Data
```
FROSClock NewClock;
TopicProxy->SetData(NewClock);
m_Writer->Write();
```

## Read Data
Add the include for DDS Reader
```
#include "Topic/DDSReader.h" 
```
### Create Reader
For create a DDS Reader, you need to setup the settings of the topic you want to read on. 
The Settings is contain in a struct called FTopicDescription. 
```
TObjectPtr<UClock_TopicProxy> ReaderTopicProxy;
UDDSReader* Reader;

FTopicDescription Settings;
Settings.SetName("rt/clock");
Settings.SetQualityOfService(QOS_TIME);

UMorseLib::CreateReader(this, Settings, UClock_TopicProxy::StaticClass(), Reader);

ReaderTopicProxy = Reader->GetTopicProxy<UClock_TopicProxy>();
```
Operation of reading on DDS. The read are goind to get the data on DDS and set up inside the topic proxy object. The updated data is acessible after this operation.
### Read data
```
ReaderTopicProxy->OnDataArrived.AddDynamic(this, &UMRS_Clock::OnMessageReceived); //Called when new data available on topic
void OnMessageReceived(FROSClock Msg)
{
    UE_LOG(LogTemp, Log, TEXT("Clock | second : %i, nanosecond : %i "), Msg.clock.sec, Msg.clock.nanosec);
};

//OR 
Reader->Read(); //This operation update the data inside the topic proxy
FClock Clock = ReaderTopicProxy->GetData(); //this operation get the data are actually stored in the topic
```

## Configure QoS and Settings
Add the include for the topic
```
#include "Topic/DDSTopic.h" 
```
Define a custom and reusable QOS.
```
inline FQoSInfo QOS_TIME = FQoSInfo{
    FQoSDurability{EQosDurability::VOLATILE, 1},						// Volatile data
    FQoSHistory{EQosHistory::KEEP_ALL, 0},							    // Keep all samples
    FQoSReliability{EQosReliability::BEST_EFFORT, 0},		            // No blocking
    FQoSLiveness{EQosLiveness::MANUAL_BY_TOPIC, 1000000000},	        // 1 second lease duration
    FQoSOwnership{EQosOwnership::SYSTEM_DEFAULT, 1},
    FQoSConsistency{EQosConsistency::SYSTEM_DEFAULT,false, false,false,false}
};

FTopicDescription Settings;
Settings.SetName("rt/clock");
Settings.SetQualityOfService(QOS_TIME);
```