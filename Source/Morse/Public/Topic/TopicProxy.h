/*****************************************************************
 * @file   TopicProxy.h
 * @brief   This file contains the implementation of a TopicProxy. A TopicProxy act like a bridge between DDS and Unreal. It hold the data of the topic and 
 * contains the conversion function. 
 * 
 * @author Nicolas B.
 * @date   March 2024
 * @copyright Nicolas Brugie. All rights reserved.
 *********************************************************************/
#pragma once 
#include "CoreMinimal.h" 
#include "ddsc/dds.h"

#include "TopicProxy.generated.h" 

 /**
  * @class UTopicProxy
  * @brief Base class for data handling. The topic proxy are the object who is in charge to allocate, and call the serialise/deserialize data function the data when they are receive
  * or send.
  * @details This class provides a base for data handling in Morse.
  */
UCLASS(BlueprintType, Blueprintable)
class MORSE_API UTopicProxy : public UObject
{
    GENERATED_BODY()

public:

    /**
     * @brief Initializes the data proxy.
     * @details This function is used for allocated the data in the TopicProxy.
     */
    UFUNCTION(BlueprintCallable)
    virtual void Initialize() {};
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
    /**
     * @brief Finalizes the data proxy..
     * @details This function is used for Data desallocation (at the end of the TopicProxy life)
     */
    UFUNCTION(BlueprintCallable)
    virtual void Terminate() {};

    /**
     * @brief Executes the message callback
     * @details This function is executed by the Reader when new data are availble. This callback can be bind to a delegate.
     */
    virtual void ExecuteMessageCallback() {};

    /**
     * @brief Gets the data.
     * @details This function returns the dds raw data.
     * @return The Data contains in the topic proxy.
     */
    virtual void* Get() { return nullptr; };

    /**
     * @brief Gets the type descriptor of the message. 
     * @details This function returns the type descriptor of the data  topic. The type descriptor is used for identify the data on the network.
     * /!\ In ROS, the type desc are not the type desc used at runtime by ROS. When we compile .idl with other compiler (like cyclone)
     * the type descriptor are like this : rcl_interfaces::msg::Log, and if we run a topic with ROS the topic descriptor are like this :
     * rcl_interfaces::msg::dds_::Log_. So, we need to modify manually the Topic descriptor to match with ROS QOS. 
     * @return The type descriptor of the message.
     */
    virtual const dds_topic_descriptor_t* GetTypeDesc()
    {
        return nullptr;
    };
};


