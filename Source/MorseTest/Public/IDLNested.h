/*****************************************************************//**
 * Generated by Morse IDL to UE Translator.
 * @file   ROSNested.h
 * @brief  File containing data structures and the definition of the message generated from the IDL.
 *         Idl Type : ROSNested.idl
 *         
 * @author Nicolas B.
 * @date   December 2023
 * @copyright Copyright 2023 Nicolas Brugie. All rights reserved.
 *********************************************************************/

#pragma once 
#include "CoreMinimal.h" 
#include "Topic/TopicProxy.h"
#include "Utils/MRSConvertUtils.h"


#include "DataImplementation/Nested.h"
#include "IDLPrimitives.h"
#include "IDLNested.generated.h"







/** @addtogroup {NameDoxygenMessageContainer}
  * @brief {NameDoxygenMessageContainer}
  *
  * @{
  */
USTRUCT(Blueprintable)
struct FIDLNested
{
    GENERATED_BODY()

public:
    /**
    * @cond
    */
    FIDLNested()
    {

    };
    /**
     * @endcond
     */

    
    UPROPERTY(EditAnywhere)
    FIDLPrimitives PrimitiveValues;
    

    /**
     * @cond
     */
    void DDSToUE (const test_msgs_msg_Nested& InData) 
    {
        PrimitiveValues.DDSToUE(InData.primitive_values);
    };

    void UEToDDS (test_msgs_msg_Nested& OutData) 
    {
        PrimitiveValues.UEToDDS(OutData.primitive_values);
    };
    
    /**
     * @endcond
     */
};
/** @} */



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FROSNestedCallback, const FIDLNested, Data);

UCLASS(BlueprintType, Blueprintable)
class MORSETEST_API UNested_TopicProxy : public UTopicProxy
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintAssignable)
    FROSNestedCallback OnDataChanged;

    virtual void Initialize() override {
        Data = test_msgs_msg_Nested__alloc();
    };

    virtual void Terminate() override {
        test_msgs_msg_Nested_free(Data, DDS_FREE_ALL);
    };

    UFUNCTION(BlueprintCallable)
    void GetData(FIDLNested& Output)
    {
        Output.DDSToUE(*Data);
    };

    UFUNCTION(BlueprintCallable)
    void SetData(FIDLNested Input)
    {
        Input.UEToDDS(*Data);
    };

    virtual void ExecuteMessageCallback() override
    {
        FIDLNested NewData;
        NewData.DDSToUE(*Data);
        OnDataChanged.Broadcast(NewData);
    };

    virtual void* Get() override
    {
        return Data;
    };

    virtual const dds_topic_descriptor_t* GetTypeDesc() override
    {
        return &test_msgs_msg_Nested_desc;
    };

private:
    test_msgs_msg_Nested* Data;
};