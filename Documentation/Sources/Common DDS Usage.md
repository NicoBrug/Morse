# Common DDS Usage

## Write Data on DDS

### Create Writer
```
TObjectPtr<UClock_TopicProxy> TopicProxy;
UDDSWriter* m_Writer;

FTopicDescription Settings;
Settings.SetName("rt/clock");
Settings.SetQualityOfService(QOS_TIME);

UMorseLib::CreateWriter(
    this,
    Settings,
    UClock_TopicProxy::StaticClass(),
    m_TopicProxy,
    m_Writer);

TopicProxy = Cast<UClock_TopicProxy>(m_TopicProxy);
```

### Write Data
```
FROSClock NewClock;
TopicProxy->SetData(NewClock);
m_Writer->Write();
```

## Read Data on DDS

### Create Reader
```
TObjectPtr<UClock_TopicProxy> ReaderTopicProxy;
UDDSReader* m_Reader;

FTopicDescription Settings;
Settings.SetName("rt/clock");
Settings.SetQualityOfService(QOS_TIME);

UMorseLib::CreateReader(
    this,
    Settings,
    UClock_TopicProxy::StaticClass(),
    m_TopicProxy,
    m_Writer);

ReaderTopicProxy = Cast<UClock_TopicProxy>(m_TopicProxy);
```

### Read data
```
ReaderTopicProxy->OnDataArrived.AddDynamic(this, &UMRS_Clock::OnMessageReceived); //Called when new data available on topic
void OnMessageReceived(FROSClock Msg)
{
    UE_LOG(LogTemp, Log, TEXT("Clock | second : %i, nanosecond : %i "), Msg.clock.sec, Msg.clock.nanosec);
};
```