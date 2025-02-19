#include "Math/MRSGeometry.h"





void FMRSQuaternion::DDSToUE(const Unreal_Math_Quaternion& InData)
{
        W = InData.W;
        X = InData.X;
        Y = InData.Y;
        Z = InData.Z;
};

void FMRSQuaternion::UEToDDS(Unreal_Math_Quaternion& OutData) 
{
        OutData.W = W;
        OutData.X = X;
        OutData.Y = Y;
        OutData.Z = Z;
};

void UQuaternion_TopicProxy::Initialize()
{
    Data = Unreal_Math_Quaternion__alloc();
};

void UQuaternion_TopicProxy::Terminate()
{
    Unreal_Math_Quaternion_free(Data, DDS_FREE_ALL);
};

const dds_topic_descriptor_t* UQuaternion_TopicProxy::GetTypeDesc()
{
     return &Unreal_Math_Quaternion_desc;
};

void* UQuaternion_TopicProxy::Get()
{
    return Data;
};

void UQuaternion_TopicProxy::ExecuteMessageCallback()
{
    FMRSQuaternion NewData;
    NewData.DDSToUE(*Data);
    OnDataChanged.Broadcast(NewData);
};

void UQuaternion_TopicProxy::GetData(FMRSQuaternion& Output)
{
    Output.DDSToUE(*Data);
};

void UQuaternion_TopicProxy::SetData(FMRSQuaternion Input)
{
    Input.UEToDDS(*Data);
};









void FMRSVector3::DDSToUE(const Unreal_Math_Vector3& InData)
{
        X = InData.X;
        Y = InData.Y;
        Z = InData.Z;
};

void FMRSVector3::UEToDDS(Unreal_Math_Vector3& OutData) 
{
        OutData.X = X;
        OutData.Y = Y;
        OutData.Z = Z;
};

void UVector3_TopicProxy::Initialize()
{
    Data = Unreal_Math_Vector3__alloc();
};

void UVector3_TopicProxy::Terminate()
{
    Unreal_Math_Vector3_free(Data, DDS_FREE_ALL);
};

const dds_topic_descriptor_t* UVector3_TopicProxy::GetTypeDesc()
{
     return &Unreal_Math_Vector3_desc;
};

void* UVector3_TopicProxy::Get()
{
    return Data;
};

void UVector3_TopicProxy::ExecuteMessageCallback()
{
    FMRSVector3 NewData;
    NewData.DDSToUE(*Data);
    OnDataChanged.Broadcast(NewData);
};

void UVector3_TopicProxy::GetData(FMRSVector3& Output)
{
    Output.DDSToUE(*Data);
};

void UVector3_TopicProxy::SetData(FMRSVector3 Input)
{
    Input.UEToDDS(*Data);
};









void FMRSAccel::DDSToUE(const Unreal_Math_Accel& InData)
{
        Linear.DDSToUE(InData.Linear);
        Angular.DDSToUE(InData.Angular);
};

void FMRSAccel::UEToDDS(Unreal_Math_Accel& OutData) 
{
        Linear.UEToDDS(OutData.Linear);
        Angular.UEToDDS(OutData.Angular);
};

void UAccel_TopicProxy::Initialize()
{
    Data = Unreal_Math_Accel__alloc();
};

void UAccel_TopicProxy::Terminate()
{
    Unreal_Math_Accel_free(Data, DDS_FREE_ALL);
};

const dds_topic_descriptor_t* UAccel_TopicProxy::GetTypeDesc()
{
     return &Unreal_Math_Accel_desc;
};

void* UAccel_TopicProxy::Get()
{
    return Data;
};

void UAccel_TopicProxy::ExecuteMessageCallback()
{
    FMRSAccel NewData;
    NewData.DDSToUE(*Data);
    OnDataChanged.Broadcast(NewData);
};

void UAccel_TopicProxy::GetData(FMRSAccel& Output)
{
    Output.DDSToUE(*Data);
};

void UAccel_TopicProxy::SetData(FMRSAccel Input)
{
    Input.UEToDDS(*Data);
};









void FMRSVector2D::DDSToUE(const Unreal_Math_Vector2D& InData)
{
        X = InData.X;
        Y = InData.Y;
};

void FMRSVector2D::UEToDDS(Unreal_Math_Vector2D& OutData) 
{
        OutData.X = X;
        OutData.Y = Y;
};

void UVector2D_TopicProxy::Initialize()
{
    Data = Unreal_Math_Vector2D__alloc();
};

void UVector2D_TopicProxy::Terminate()
{
    Unreal_Math_Vector2D_free(Data, DDS_FREE_ALL);
};

const dds_topic_descriptor_t* UVector2D_TopicProxy::GetTypeDesc()
{
     return &Unreal_Math_Vector2D_desc;
};

void* UVector2D_TopicProxy::Get()
{
    return Data;
};

void UVector2D_TopicProxy::ExecuteMessageCallback()
{
    FMRSVector2D NewData;
    NewData.DDSToUE(*Data);
    OnDataChanged.Broadcast(NewData);
};

void UVector2D_TopicProxy::GetData(FMRSVector2D& Output)
{
    Output.DDSToUE(*Data);
};

void UVector2D_TopicProxy::SetData(FMRSVector2D Input)
{
    Input.UEToDDS(*Data);
};









void FMRSTransform::DDSToUE(const Unreal_Math_Transform& InData)
{
        Rotation.DDSToUE(InData.Rotation);
        Scale3d.DDSToUE(InData.Scale3D);
        Translation.DDSToUE(InData.Translation);
};

void FMRSTransform::UEToDDS(Unreal_Math_Transform& OutData) 
{
        Rotation.UEToDDS(OutData.Rotation);
        Scale3d.UEToDDS(OutData.Scale3D);
        Translation.UEToDDS(OutData.Translation);
};

void UTransform_TopicProxy::Initialize()
{
    Data = Unreal_Math_Transform__alloc();
};

void UTransform_TopicProxy::Terminate()
{
    Unreal_Math_Transform_free(Data, DDS_FREE_ALL);
};

const dds_topic_descriptor_t* UTransform_TopicProxy::GetTypeDesc()
{
     return &Unreal_Math_Transform_desc;
};

void* UTransform_TopicProxy::Get()
{
    return Data;
};

void UTransform_TopicProxy::ExecuteMessageCallback()
{
    FMRSTransform NewData;
    NewData.DDSToUE(*Data);
    OnDataChanged.Broadcast(NewData);
};

void UTransform_TopicProxy::GetData(FMRSTransform& Output)
{
    Output.DDSToUE(*Data);
};

void UTransform_TopicProxy::SetData(FMRSTransform Input)
{
    Input.UEToDDS(*Data);
};



