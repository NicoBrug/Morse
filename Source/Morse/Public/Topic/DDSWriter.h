/*****************************************************************//**
 * @file   DDSWriter.h
 * @brief  Classe permettant d'�crire des donn�es sur DDS. Le writer �crit sur un topic.
 * 
 * @author Nicolas B.as B.
 * @date   March 2024
 * @copyright Nicolas Brugie. All rights reserved.
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ddsc/dds.h"

#include "Topic/DDSTopic.h"
#include "Participant/DDSParticipant.h"

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
	/**
	 * @brief Constructs a new UDDSWriter object.
	 *
	 * This function initializes the UDDSWriter with the given object initializer
	 * and sets the entity type to WRITER.
	 *
	 * @param Initializer An object of FObjectInitializer used to initialize the writer.
	 * @return A new instance of UDDSWriter.
	 */
	UDDSWriter(const FObjectInitializer& Initializer);

	/**
	 * @brief Handles the destruction process for the UDDSWriter object.
	 *
	 * This override method ensures that proper cleanup is performed before the
	 * UDDSWriter object is destroyed. It calls the Fini method to finalize any
	 * ongoing DDS processes and then invokes the parent class's BeginDestroy method.
	 *
	 * The Fini method handles the cleanup of the m_WriterTopic member and deletion
	 * of the DDS entity associated with the writer.
	 */
	virtual void BeginDestroy() override;

	/**
	 * Initializes the writer.
	 */
	UFUNCTION(BlueprintCallable)
	void Initialize(UDDSParticipant* OwnerParticipant)
	{
		SetParticipant(OwnerParticipant);
		Initialize();
	};

	/**
	 * Initializes the UDDSWriter instance.
	 *
	 * This method sets up the DDS writer entity with the specified quality of service (QoS)
	 * and associates it with the corresponding participant and topic entities. It verifies
	 * the validity of the participant and topic before proceeding with the creation of the
	 * writer entity. Upon successful initialization, the status mask for publication-matched
	 * events is set, and the state of the writer is updated to `INITIALIZED`.
	 *
	 * Preconditions:
	 * - The owner participant (`m_OwnerParticipant`) must be valid.
	 * - The writer topic (`m_WriterTopic`) must be valid.
	 *
	 * Error Handling:
	 * - The method uses `RC_DDS_CHECK` macro to log any errors that occur during the
	 *   DDS entity creation.
	 */
	virtual void Initialize() override;

	/**
	 * @brief Clear any DDS Entity Holding by the Writer
	 */
	UFUNCTION(BlueprintCallable)
	virtual void Terminate() override;

	
	UFUNCTION(BlueprintCallable, Category = "Topics")
	void SetTopic(UDDSTopic* WriterTopic)
	{
		m_WriterTopic = WriterTopic;
	};
	
	UFUNCTION(BlueprintCallable, Category = "Topics")
	void SetParticipant(UDDSParticipant* OwnerParticipant)
	{
		m_OwnerParticipant = OwnerParticipant;
	};
	
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
	UDDSTopic* m_WriterTopic;
	
	UPROPERTY()
	UDDSParticipant* m_OwnerParticipant;

private:
	/**
	 * @brief Holds the status code related to the current operation or state of the software component.
	 *
	 * This variable is used to store an unsigned integer that represents various status codes.
	 * The meaning of these codes is defined by the specific software component or module that uses this variable.
	 */
	uint32_t m_uiStatus = 0; 

};
