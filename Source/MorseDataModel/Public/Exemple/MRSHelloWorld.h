/*****************************************************************//**
 * Generated by Morse IDL to UE Translator.
 * @file   MRSHelloWorld.h
 * @brief  File containing data structures and the definition of the message generated from the IDL.
 *         Idl Type : MRSHelloWorld.idl
 *         
 * @author Nicolas B.
 * @date   December 2023
 * @copyright Copyright 2023 Nicolas Brugie. All rights reserved.
 *********************************************************************/

#pragma once 
#include "CoreMinimal.h" 
#include "Topic/TopicProxy.h"


#include "CycloneImpl/Exemple/HelloWorld.h"

#include "MRSHelloWorld.generated.h" 



USTRUCT(Blueprintable)
struct FMRSHelloWorld
{
    GENERATED_BODY()

    FMRSHelloWorld()
    {

    };

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Hellostr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Hellofloat = 0.0f;
    

    void DDSToUE(const Unreal_Exemple_HelloWorld& InData);
    void UEToDDS(Unreal_Exemple_HelloWorld& OutData);
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMRSHelloWorldCallback, const FMRSHelloWorld, Data);

UCLASS(BlueprintType, Blueprintable)
class MORSEDATAMODEL_API UHelloWorld_TopicProxy : public UTopicProxy
{
    GENERATED_BODY()

    UPROPERTY(BlueprintAssignable)
    FMRSHelloWorldCallback OnDataChanged;

    /** Begin implement TopicProxy Interface */
    virtual void Initialize() override;
    virtual void Terminate() override;
    virtual const dds_topic_descriptor_t* GetTypeDesc() override;
    virtual void* Get() override;
    virtual void ExecuteMessageCallback() override;
    /** End implement TopicProxy Interface */

    UFUNCTION(BlueprintCallable)
    void GetData(FMRSHelloWorld& Output);

    UFUNCTION(BlueprintCallable)
    void SetData(FMRSHelloWorld Input);

private:
    Unreal_Exemple_HelloWorld* Data;
};