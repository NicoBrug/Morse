/*****************************************************************
* @file   DDSEntity.h
 * @brief  This file contains the implementation of the abstract class who represent a DDS Entity.
 * A DDS Entity https://fast-dds.docs.eprosima.com/en/latest/fastdds/dds_layer/core/entity/entity.html
 * 
 * @author nicol
 * @date   January 2025
 * @copyright Copyright 2023 NicoBrugie. All rights reserved.
 *********************************************************************/
#pragma once

#include "ddsc/dds.h"
#include "QoS/DDSQoS.h"

/**
 * @brief Enumeration for the state of an entity.
 */
UENUM()
enum class EEntityState
{
	NOT_INITIALIZED, /**< Entity has not been initialized. */
	INITIALIZED, /**< Entity has been initialized. */
	ST_ERROR, /**< Entity has encoutred an error */
	DESTROYED /**< Entity has been destroyed. Memory Is Free. */
};

/**
 * @brief Enumeration for the type of an entity (According to DDS Specification).
 */
UENUM()
enum class EEntityType
{
	PUBLISHER, /**< The entity is a publisher. */
	SUBSCRIBER, /**< The entity is a subscriber. */
	READER, /**< The entity is a reader. */
	WRITER, /**< The entity is a writer. */
	READ_CONDITION, /**< The entity is a read condition. */
	TOPIC, /**< The entity is a topic. */
	NONE /**< The entity type is not specified. */
};

/**
 * @class UDDSEntity
 * @brief Base class for DDS (Data Distribution Service) entities.
 */
class MORSE_API UDDSEntity
{
public:

	/**
	 * @brief Default constructor that initializes the entity state to NOT_INITIALIZED.
	 */
	UDDSEntity() : State(EEntityState::NOT_INITIALIZED) {}

	/**
	 * @brief Virtual function to initialize the entity. Can be overridden by derived classes. Entity memory is allocated here (derived class).
	 */
	virtual void Initialize() {};

	/**
	 * @brief Virtual function to terminate the entity. Can be overridden by derived classes. Entity memory is here (derived class). 
	 */
	virtual void Terminate() {};

	/**
	 * @brief Get the type of the entity.
	 * @return The type of the entity as an EEntityType.
	 */
	EEntityType GetType() const
	{
		return Type;
	};

	/**
	 * @brief Set the DDS Type of an entity.
	 * @param NewType The new type to set.
	 */
	void SetType(EEntityType NewType)
	{
		Type = NewType;
	};
	
	/**
	 * @brief Get the underlying DDS entity handle.
	 * @return The DDS entity handle.
	 */
	dds_entity_t GetEntity() const
	{
		return EntityHandler;
	};

	/**
	 * @brief Get the current state of the entity.
	 * @return The current state of the entity as an EEntityState.
	 */
	EEntityState GetState() const 
    {
    	return State;
    };

	/**
	 * @brief Set the state of the entity.
	 * @param NewState The new state to set.
	 */
	void SetState(EEntityState NewState)
	{
		State = NewState;
	};

	/**
	 * @brief Get the current Quality of Service (QoS) settings of the entity.
	 * @return The current QoS settings as an FQoSInfo object.
	 */
	FQoSInfo GetQoS() const
	{
		return QoS;
	};

	/**
	 * @brief Set the Quality of Service (QoS) settings for the entity.
	 * @param InQoS The new QoS settings to apply.
	 */
	void SetQoS(FQoSInfo InQoS)
	{
		QoS = InQoS;
	};

	/**
	 * @brief Check if the entity has been destroyed.
	 * @return True if the entity state is DESTROYED, false otherwise.
	 */
	bool IsEntityDestroyed() const
	{
		return State == EEntityState::DESTROYED;	
	};

protected:
	/** @brief Current state of the entity. */
	EEntityState State; 

	/** @brief Current Quality of Service (QoS) settings for the entity. */
	FQoSInfo QoS;

	/** @brief Type of the entity. Defaults to NONE. */
	EEntityType Type = EEntityType::NONE;
	
	/** @brief Handle to the underlying DDS entity. */
	dds_entity_t EntityHandler;
};