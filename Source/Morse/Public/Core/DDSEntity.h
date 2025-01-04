#pragma once

#include "ddsc/dds.h"
#include "QoS/DDSQoS.h"

UENUM()
enum class EEntityState
{
	NOT_INITIALIZED,
	INITIALIZED,
	DESTROYED
};

UENUM()
enum class EEntityType
{
	PUBLISHER,
	SUBSCRIBER,
	READER,
	WRITER,
	READ_CONDITION,
	TOPIC,
	NONE
};

class MORSE_API UDDSEntity
{
public:

	UDDSEntity() : m_State(EEntityState::NOT_INITIALIZED) {} // Initialiser l'état à Uninitialized lors de la création de l'objet

	virtual void Init() {};
	virtual void Fini() {};

	EEntityType GetType()
	{
		return m_Type;
	};

	dds_entity_t GetEntity()
	{
		return m_Entity;
	};

	void SetQoS(FQoSInfo InQoS)
	{
		m_CurrentQoS = InQoS;
	};

	FQoSInfo m_CurrentQoS;
	EEntityType m_Type = EEntityType::NONE; //Type de l'entité

protected:
	EEntityState m_State; // État actuel de l'entité

	dds_entity_t m_Entity;
};