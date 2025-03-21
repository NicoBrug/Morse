/*****************************************************************//**
 * Generated by Morse IDL to UE Translator.
 * @file   ROSPrimitives.h
 * @brief  File containing data structures and the definition of the message generated from the IDL.
 *         Idl Type : ROSPrimitives.idl
 *         
 * @author Nicolas B.
 * @date   December 2023
 * @copyright Copyright 2023 Nicolas Brugie. All rights reserved.
 *********************************************************************/

#pragma once 
#include "CoreMinimal.h" 
#include "DataImplementation/Primitives.h"
#include "Topic/TopicProxy.h"
#include "Utils/MRSConvertUtils.h"

#include "IDLPrimitives.generated.h" 







/** @addtogroup {NameDoxygenMessageContainer}
  * @brief {NameDoxygenMessageContainer}
  *
  * @{
  */
USTRUCT(Blueprintable)
struct FIDLPrimitives
{
    GENERATED_BODY()

public:
    /**
    * @cond
    */
    // Constructeur par défaut
    FIDLPrimitives(){}

    FIDLPrimitives(
        bool InBoolValue,
        char InByteValue,
        char InCharValue,
        float InFloat32Value,
        double InFloat64Value,
        int8 InInt8Value,
        uint8 InUInt8Value,
        int16 InInt16Value,
        uint16 InUInt16Value,
        int32 InInt32Value,
        uint32 InUInt32Value,
        int64 InInt64Value,
        uint64 InUInt64Value,
        const FString& InStringValue)
        : BoolValue(InBoolValue),
          ByteValue(InByteValue),
          CharValue(InCharValue),
          Float32Value(InFloat32Value),
          Float64Value(InFloat64Value),
          Int8Value(InInt8Value),
          Uint8Value(InUInt8Value),
          Int16Value(InInt16Value),
          Uint16Value(InUInt16Value),
          Int32Value(InInt32Value),
          Uint32Value(InUInt32Value),
          Int64Value(InInt64Value),
          Uint64Value(InUInt64Value),
          StringValue(InStringValue)
    {
    }
    /**
     * @endcond
     */

    
    UPROPERTY(EditAnywhere)
    bool BoolValue = false;
    
    char ByteValue;
    
    unsigned char CharValue;
    
    UPROPERTY(EditAnywhere)
    float Float32Value = 0.0f;
    
    UPROPERTY(EditAnywhere)
    double Float64Value = 0.0;
    
    char Int8Value;
    
    uint8 Uint8Value;
    
    UPROPERTY(EditAnywhere)
    int16 Int16Value = 0;
    
    UPROPERTY(EditAnywhere)
    uint16 Uint16Value = 0;
    
    UPROPERTY(EditAnywhere)
    int32 Int32Value = 0;
    
    UPROPERTY(EditAnywhere)
    unsigned int Uint32Value = 0;
    
    UPROPERTY(EditAnywhere)
    int64 Int64Value = 0;
    
    UPROPERTY(EditAnywhere)
    uint64 Uint64Value = 0;
    
    UPROPERTY(EditAnywhere)
    FString StringValue;
    

    /**
     * @cond
     */
    void DDSToUE (const test_msgs_msg_Primitives& InData) 
    {
        BoolValue = InData.bool_value;
        ByteValue = InData.byte_value;
        CharValue = InData.char_value;
        Float32Value = InData.float32_value;
        Float64Value = InData.float64_value;
        Int8Value = InData.int8_value;
        Uint8Value = InData.uint8_value;
        Int16Value = InData.int16_value;
        Uint16Value = InData.uint16_value;
        Int32Value = InData.int32_value;
        Uint32Value = InData.uint32_value;
        Int64Value = InData.int64_value;
        Uint64Value = InData.uint64_value;
        MRSConvertUtils::DDSStringToUE( InData.string_value, StringValue);
    };

    void UEToDDS (test_msgs_msg_Primitives& OutData) 
    {
        OutData.bool_value = BoolValue;
        OutData.byte_value = ByteValue;
        OutData.char_value = CharValue;
        OutData.float32_value = Float32Value;
        OutData.float64_value = Float64Value;
        OutData.int8_value = Int8Value;
        OutData.uint8_value = Uint8Value;
        OutData.int16_value = Int16Value;
        OutData.uint16_value = Uint16Value;
        OutData.int32_value = Int32Value;
        OutData.uint32_value = Uint32Value;
        OutData.int64_value = Int64Value;
        OutData.uint64_value = Uint64Value;
        MRSConvertUtils::UEStringToDDS(StringValue, OutData.string_value );
    };
    
    /**
     * @endcond
     */
};
/** @} */



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FROSPrimitivesCallback, const FIDLPrimitives, Data);

UCLASS(BlueprintType, Blueprintable)
class MORSETEST_API UPrimitives_TopicProxy : public UTopicProxy
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintAssignable)
    FROSPrimitivesCallback OnDataChanged;

    virtual void Initialize() override {
        Data = test_msgs_msg_Primitives__alloc();
    };

    virtual void Terminate() override {
        test_msgs_msg_Primitives_free(Data, DDS_FREE_ALL);
    };

    UFUNCTION(BlueprintCallable)
    void GetData(FIDLPrimitives& Output)
    {
        Output.DDSToUE(*Data);
    };

    UFUNCTION(BlueprintCallable)
    void SetData(FIDLPrimitives Input)
    {
        Input.UEToDDS(*Data);
    };

    virtual void ExecuteMessageCallback() override
    {
        FIDLPrimitives NewData;
        NewData.DDSToUE(*Data);
        OnDataChanged.Broadcast(NewData);
    };

    virtual void* Get() override
    {
        return Data;
    };

    virtual const dds_topic_descriptor_t* GetTypeDesc() override
    {
        return &test_msgs_msg_Primitives_desc;
    };

private:
    test_msgs_msg_Primitives* Data;
};