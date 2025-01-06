/*****************************************************************
 * @file   MRS_BaseNode.h
 * @brief  
 * 
 * @author nicol
 * @date   January 2024
 * @copyright Copyright 2023 NicoBrugie. All rights reserved.
    This project is released under the GNU Public License.
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Core/DDSEntity.h"
#include "Topic/DDSTopic.h"
#include "Core/MorseEngineSubsystem.h" //Used for topic description TODO :Move into DDSTopic or make custom file
#include "MRS_BaseNode.generated.h"

/**
 * @brief TODO : Implementaiotn of the Node logic. A node can handle mutiple entities (reader writer etc). This can be
 * used for complex or reusable dds opération. The nodes is spin inside the Executor. 
 * NOT USED FOR THE MOMENT (BP Only)
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
    FOnHealthChanged // Name of the structure that will be generated
);

// Cette ligne est n�cessaire pour g�n�rer le code n�cessaire � l'interface
UINTERFACE(BlueprintType)
class MORSE_API UMorseNodeInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * Interface pour les noeuds de Morse
 */
class MORSE_API IMorseNodeInterface
{
    GENERATED_BODY()

public:

    // D�clare une fonction BlueprintNativeEvent pour �tre override dans Blueprint
    UFUNCTION(BlueprintNativeEvent, Category = "Node")
    void OnLaunch();
    virtual void OnLaunch_Implementation() {};

    UFUNCTION(BlueprintNativeEvent, Category = "Node")
    void OnStop();
    virtual void OnStop_Implementation() {};
};

UCLASS(Blueprintable, BlueprintType)
class MORSE_API UMRS_BaseNode : public UObject
{

    GENERATED_BODY()

public:
    UMRS_BaseNode() {};

    UFUNCTION(BlueprintNativeEvent, Category = "Node")
    void OnLaunch();
    virtual void OnLaunch_Implementation() {};

    UFUNCTION(BlueprintNativeEvent, Category = "Node")
    void OnStop();
    virtual void OnStop_Implementation() {};

    virtual void Launch() {};
    virtual void Stop() {};

    /**
     * @brief Operation for create a new topic with specified QOS.
     *
     * @param Params
     * @param QoS
     * @return
     */
    UFUNCTION(BlueprintCallable, Category = "Topics")
    UDDSTopic* CreateTopic(FTopicDescription Params, FQoSInfo QoS = FQoSInfo());

    /**
     * @brief Operation for create a new writer with specified QOS.
     *
     * @param Topic
     * @param QoS
     * @return
     */
    UFUNCTION(BlueprintCallable, Category = "Topics")
    UDDSWriter* CreateWriter(UDDSTopic* Topic, FQoSInfo QoS = FQoSInfo());

    /**
     * @brief Operation for create a new reader with specified QOS.
     *
     * @param Topic
     * @param QoS
     * @return
     */
    UFUNCTION(BlueprintCallable, Category = "Topics")
    UDDSReader* CreateReader(UDDSTopic* Topic, FQoSInfo QoS = FQoSInfo());


    void SetParticipant(UDDSParticipant* Participant)
    {
        m_Participant = Participant;
    };

    TArray<UDDSEntity*> m_OnlineEntities;

    UPROPERTY(BlueprintAssignable)
    FOnHealthChanged OnHealthChanged;

private:
    UDDSParticipant* m_Participant; //default participant of morse, ALL the entity will be created with this participant

};