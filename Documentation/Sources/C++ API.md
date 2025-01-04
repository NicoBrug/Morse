# C++ API


# Write Data on DDS
Add the include for DDS Writer
```
#include "Topic/DDSWriter.h" 
```
For create a DDS Writer, you need to setup the settings of the topic you want to write on. 
The Settings is contain in a struct called FTopicDescription. 
```
UMorseLib::CreateWriter(Owner, Settings, UDataProxy::StaticClass(), TopicProxy, Writer);
```
Operation of writing the data inside the topic proxy on DDS. Before that, you can modify the data inside the topic proxy. 
```
Writer->Write();
```

# Read
Add the include for DDS Reader
```
#include "Topic/DDSReader.h" 

```
Create Reader
```
UMorseLib::CreateReader(this, Settings, UDataProxy::StaticClass(), TopicProxy, Reader);
```
Operation of reading on DDS. The read are goind to get the data on DDS and set up inside the topic proxy object. The updated data is acessible after this operation.
```
Reader->Read();
```

# Configure QOS
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

