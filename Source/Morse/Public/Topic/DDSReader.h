/*****************************************************************
 * @file   DDSReader.h
 * @brief  This file contains the implementation of a DDS Reader. A data reader can read Data on the DDS Global Data Space.
 * 
 * @author Nicolas B.
 * @date   March 2024
 * @copyright Nicolas Brugie. All rights reserved.
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ddsc/dds.h"

#include "Topic/DDSTopic.h"
#include "Participant/DDSParticipant.h"

#include "DDSReader.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MORSE_API UDDSReader : public UObject, public UDDSEntity
{
	GENERATED_BODY()

public:
	
	UDDSReader(const FObjectInitializer& Initializer);
	
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable)
	void Initialize(UDDSParticipant* InOwnerParticipant)
	{
		SetParticipant(InOwnerParticipant);
		Initialize();
	};

	virtual void Initialize() override;
	virtual void Terminate() override;
	
	// Define a static callback function
	static void DataAvailableHandler(dds_entity_t Reader, void* Arg)
	{
		if(Reader == 0)
			return;
		
		UDDSReader* ReaderInstance = static_cast<UDDSReader*>(Arg);
		if (ReaderInstance)
		{
			ReaderInstance->OnDataAvailable(Reader);
		}
	}

	// Non-static member function to handle data
	void OnDataAvailable(dds_entity_t reader)
	{
		Read();
		if(Topic && Topic->GetTopicProxy())
			Topic->GetTopicProxy()->ExecuteMessageCallback();
	};

	UFUNCTION(BlueprintCallable, Category = "Topics")
	UDDSTopic* GetTopic()
	{
		return Topic;
	};

	template <typename T>
	T* GetTopicProxy()
	{
		if(!Topic)
			return nullptr;
		
		return Topic->GetProxy<T>();
	};
	
	/**
	 * @brief Sets the DDS topic for the reader.
	 *
	 * This method assigns a specific DDS topic to the reader, allowing it to
	 * receive and process data from that topic.
	 *
	 * @param ReaderTopic Pointer to the UDDSTopic object to be associated with the reader.
	 */
	void SetTopic(UDDSTopic* ReaderTopic)
	{
		Topic = ReaderTopic;
	};

	/**
	 * @brief Sets the DDS participant for this reader.
	 *
	 * This method assigns the provided UDDSParticipant instance to the reader.
	 * It is used to establish the ownership of the reader by a specific DDS participant.
	 *
	 * @param OwnerParticipant A pointer to the UDDSParticipant instance that will own this reader.
	 */
	void SetParticipant(UDDSParticipant* InOwnerParticipant)
	{
		OwnerParticipant = InOwnerParticipant;
	};

	/**
	 * @brief Reads data from the DDS (Data Distribution Service) topic.
	 *
	 * This method retrieves data samples from the DDS topic associated with the reader.
	 * It checks if the reader's topic is valid, and if so, attempts to read one sample
	 * of data from the DDS. The read data is handled based on the provided entity.
	 * If the read operation fails, an error is logged.
	 *
	 * @throw DDS_ERR_xxx If the DDS read operation fails.
	 */
	UFUNCTION(BlueprintCallable)
	void Read();

	/**
	 * @brief The topic associated with this DDS Reader.
	 *
	 * This member holds a reference to the UDDSTopic object that this reader
	 * is subscribed to. It is used to retrieve and process incoming data
	 * associated with the topic.
	 */
	UPROPERTY()
	UDDSTopic* Topic;

	/**
	 * Pointer to the UDDSParticipant instance that owns this reader.
	 */
	UPROPERTY()
	UDDSParticipant* OwnerParticipant;

	/**
	 * @brief Listener for Data Distribution Service (DDS) events.
	 *
	 * This member is utilized to handle incoming data events for a DDS reader.
	 * It is initialized using `dds_create_listener` and configured with specific
	 * callback functions, such as `dds_lset_data_available_arg`, to manage the data
	 * availability logic. Once the DDS reader is no longer needed, the listener
	 * should be properly cleaned up using `dds_delete_listener` to prevent resource leaks.
	 *
	 * @note This listener is critical for ensuring the DDS reader can respond to data
	 *       events as they occur.
	 */
	dds_listener_t* Listener;

	/**
	 * @brief Size of the buffer used by the DDS reader.
	 *
	 * This variable holds the size of the buffer that the DDS reader uses for
	 * storing data. It is utilized to ensure that the reader has adequate space
	 * to accommodate the incoming data. Adjusting the buffer size can help in
	 * optimizing the performance and memory utilization of the DDS reader.
	 */
	size_t SizeBuff;
};
