/*****************************************************************
 * @file   RosBlueprintFunctionLibrary.h
 * @brief  C++ and Blueprint API for simplify the creation of Publisher and Subscriber
 * 
 * @author nicol
 * @date   January 2024
 * @copyright Copyright 2023 NicoBrugie. All rights reserved.
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Topic/TopicProxy.h"
#include "MorseBlueprintLib.generated.h"

/**
 * 
 */
UCLASS()
class MORSE_API UMorseLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/**
	 * @brief Creates a DDS Writer to publish data on a specified topic.
	 * 
	 * This static function creates a DDS Writer, based on input settings (& DataTyp). 
	 * publish data on the given topic using the specified data type and QoS settings.
	 *
	 * @param Owner The owner of this writer (likely the actor or object responsible for it).
	 * @param Settings The topic on which the writer will publish data.
	 * @param DataType The type of data (subclass of UTopicProxy) that this writer will publish.
	 * @param OutTopicProxy Reference to the data proxy object that will handle data.
	 * @param OutWriter Reference to the created DDS Writer.
	 * @return true if the writer was successfully created; false otherwise.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static bool CreateWriterBlueprint(UObject* Owner, FTopicDescription Settings, TSubclassOf<UTopicProxy> DataType, UTopicProxy*& OutTopicProxy, UDDSWriter*& OutWriter);
	static bool CreateWriter(UObject* Owner, FTopicDescription Settings, TSubclassOf<UTopicProxy> DataType, UDDSWriter*& OutWriter);
	
	
	/**
	 * @brief Creates a DDS Reader to subscribe to a specified topic.
	 *
	 * This static function creates a DDS Reader, based on input settings.
	 * Read data on the given topic based on the QoS settings and DataType. 
	 * 
	 *
	 * @param Owner The owner of this reader (likely the actor or object responsible for it).
	 * @param Topic The topic from which the reader will subscribe to data.
	 * @param DataType The type of data (subclass of UTopicProxy) that this reader will subscribe to.
	 * @param QoS The Quality of Service (QoS) settings for the reader.
	 * @param OutTopicProxy Reference to the data proxy object that will handle received data.
	 * @param OutReader Reference to the created DDS Reader.
	 * @return true if the reader was successfully created; false otherwise.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static bool CreateReaderBlueprint(UObject* Owner, FTopicDescription Settings, TSubclassOf<UTopicProxy> DataType, UTopicProxy*& OutTopicProxy, UDDSReader*& OutReader);
	static bool CreateReader(UObject* Owner, FTopicDescription Settings, TSubclassOf<UTopicProxy> DataType, UDDSReader*& OutReader);
};
