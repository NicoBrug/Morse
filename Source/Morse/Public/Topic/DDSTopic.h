/*****************************************************************//**
 * @file   DDSTopic.h
 * @brief  Classe repr�sentant le concept de topic dans DDS. 
 * 
 * @author Nicolas B.
 * @date   March 2024
 * @copyright Nicolas Brugie. All rights reserved.
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "TopicProxy.h"
#include "UObject/NoExportTypes.h"
#include "ddsc/dds.h"
#include "Participant/DDSParticipant.h"
#include "DDSTopic.generated.h"


/**
 * @class UDDSTopic
 * @brief Represents a topic in the DDS (Data Distribution Service).
 */
UCLASS(Blueprintable, BlueprintType)
class MORSE_API UDDSTopic : public UObject, public UDDSEntity
{
	GENERATED_BODY()
	
public:
	
	/**
	 * @brief Basic Constructor of a UObject
	 * 
	 * @param Initializer
	 */
	UDDSTopic(const FObjectInitializer& Initializer);

	UFUNCTION(BlueprintCallable)
	void Initialize(UDDSParticipant* OwnerParticipant)
	{
		SetParticipant(OwnerParticipant);
		Init();
	};

	/**
	 * @brief Operation for initialized the Topic. Memory allocation for the topic is made here.
	 *  SUCCESS STATE : EEntityState::INITIALIZED
	 *  ERROR   STATE : EEntityState::NOT_INITIALIZED
	 */
	void Init() override;

	/**
	 * @brief Operation call at the destruction of the object. The memory deallocation of the topic is made here.
	 */
	UFUNCTION(BlueprintCallable)
	void Fini() override;

	/**
	 * @brief Operation for settings the participant owner of the topic.
	 * 
	 * @param participant
	 */
	void SetParticipant(UDDSParticipant* participant)
	{
		m_OwnerParticipant = participant;
	};

	/**
	 * @brief Set the current compatible data type topic. 
	 * 
	 * @param MsgClass : TSubclassOf<UTopicProxy>, the data type the proxy need to used.
	 */
	void SetMessageType(TSubclassOf<UTopicProxy> MsgClass);

	/**
	 * @brief Get the data proxy of the Topic 
	 * 
	 * @return UTopicProxy the interface af a Data definition.
	 */
	UFUNCTION(BlueprintCallable, Category = "MRS TopicProxy")
	UTopicProxy* GetTopicProxy()
	{
		if (!IsValid(m_TopicProxy))
			return nullptr;

		return m_TopicProxy;
	};
	
	void SetName(FString Name)
	{
		m_Name = Name;
	};

	FString GetName()
	{
		return m_Name;
	};
	
	/**
	 * @brief Pointer to the associated TopicProxy object.
	 */
	UPROPERTY()
	TObjectPtr<UTopicProxy> m_TopicProxy;

	/**
	 * @brief Contains Quality of Service settings for the DDS topic.
	 *
	 * This member variable holds an instance of the FQoSInfo structure,
	 * which defines the QoS policies for the DDS topic associated with
	 * the UDDSTopic object.
	 */
	FQoSInfo m_QosInfo;

	/**
	 * @brief Pointer to the owning DDS Participant.
	 * Using at creation of the topic.
	 */
	UPROPERTY()
	UDDSParticipant* m_OwnerParticipant;
	
private :
	/**
     * @brief Holds the name of the DDS Topic.
     */
	 FString m_Name;
};
