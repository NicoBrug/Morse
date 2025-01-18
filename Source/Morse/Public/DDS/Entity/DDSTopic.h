/*****************************************************************
 * @file   DDSTopic.h
 * @brief   This file contains the implementation of a DDS Topic. A topic is the most basic description of data that can be read/write.
 * A topic connect a DDS Data Reader and a Data Writer.
 * Topic : https://fast-dds.docs.eprosima.com/en/latest/fastdds/dds_layer/topic/topic.html
 * 
 * @author Nicolas B.
 * @date   March 2024
 * @copyright Nicolas Brugie. All rights reserved.
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Topic/TopicProxy.h"
#include "ddsc/dds.h"
#include "DDS/Entity/DDSEntity.h"
#include "DDS/Entity/DDSParticipant.h"
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
	void Initialize(UDDSParticipant* InOwnerParticipant)
	{
		SetParticipant(InOwnerParticipant);
		Initialize();
	};

	//~ Begin UDDSEntity Interface.
	virtual void Initialize() override;
	virtual void Terminate() override;
	//~ End UDDSEntity Interface.

	/**
	 * @brief Operation for settings the participant owner of the topic.
	 * 
	 * @param participant
	 */
	void SetParticipant(UDDSParticipant* participant)
	{
		OwnerParticipant = participant;
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
		if (!IsValid(TopicProxy))
			return nullptr;

		return TopicProxy;
	};

	/**
	 * @brief Retrieve the topic as a specified type.
	 * @tparam T The desired type of the topic.
	 * @return A pointer to the topic of type T, or nullptr if the cast fails.
	 */
	template <typename T>
	T* GetProxy()
	{
		if (!IsValid(TopicProxy))
		{
			// Log a warning if the topic is invalid.
			UE_LOG(LogTemp, Warning, TEXT("Topic is invalid."));
			return nullptr;
		}

		// Attempt to cast the topic to the specified type.
		T* CastedTopic = Cast<T>(TopicProxy);
		if (!CastedTopic)
		{
			// Log an error if the cast fails.
			UE_LOG(LogTemp, Error, TEXT("Failed to cast Topic to the specified type: %s"), *T::StaticClass()->GetName());
		}

		return CastedTopic;
	};
	
	void SetName(FString InName)
	{
		TopicName = InName;
	};

	FString GetName()
	{
		return TopicName;
	};
	
	/**
	 * @brief Pointer to the associated TopicProxy object.
	 */
	UPROPERTY()
	TObjectPtr<UTopicProxy> TopicProxy;

	/**
	 * @brief Pointer to the owning DDS Participant.
	 * Using at creation of the topic.
	 */
	UPROPERTY()
	UDDSParticipant* OwnerParticipant;
	
private :
	/**
     * @brief Holds the name of the DDS Topic.
     */
	 FString TopicName;
};
