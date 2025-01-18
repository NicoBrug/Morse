/*****************************************************************
 * @file   DDSWriter.h
 * @brief  This file contains the implementation of a DDS Writer. A data writer can write Data on the DDS Global Data Space.
 * Writer : https://fast-dds.docs.eprosima.com/en/latest/fastdds/dds_layer/publisher/dataWriter/dataWriter.html
 * 
 * @author Nicolas B
 * @date   March 2024
 * @copyright Nicolas Brugie. All rights reserved.
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "ddsc/dds.h"
#include "DDS/Entity/DDSEntity.h"
#include "DDS/Entity/DDSParticipant.h"
#include "DDS/Entity/DDSTopic.h"

#include "DDSWriter.generated.h"

/**
 * @class UDDSWriter
 * @brief A class responsible for writing Data On DDS.
 *
 * The UDDSWriter class provides functionality to write user defined DDSData on specific Topic. 
 */
UCLASS(Blueprintable, BlueprintType)
class MORSE_API UDDSWriter : public UObject, public UDDSEntity
{
	GENERATED_BODY()

public:

	UDDSWriter(const FObjectInitializer& Initializer);
	
	/**
	 * Initializes the writer.
	 */
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

	UFUNCTION(BlueprintCallable, Category = "Topics")
	UDDSTopic* GetTopic();

	template <typename T>
	T* GetTopicProxy()
	{
		if(!Topic)
			return nullptr;
		
		return Topic->GetProxy<T>();
	};
	
	UFUNCTION(BlueprintCallable, Category = "Topics")
	void SetTopic(UDDSTopic* WriterTopic);
	
	UFUNCTION(BlueprintCallable, Category = "Topics")
	void SetParticipant(UDDSParticipant* InOwnerParticipant);
	
	UFUNCTION(BlueprintCallable, Category = "Topics")
	void Write();

	/**
	 * @brief Represents the DDS topic associated with the writer.
	 *
	 * This variable holds a pointer to a UDDSTopic instance, which is the topic
	 * used by the DDS writer to publish messages. It must be initialized and set
	 * before the writer can be used to publish data successfully. 
	 */
	UPROPERTY()
	UDDSTopic* Topic;
	
	UPROPERTY()
	UDDSParticipant* OwnerParticipant;

private:
	/**
	 * @brief Holds the status code related to the current operation or state of the software component.
	 *
	 * This variable is used to store an unsigned integer that represents various status codes.
	 * The meaning of these codes is defined by the specific software component or module that uses this variable.
	 */
	uint32_t EntityDDSStatus = 0; 
};
