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

	UDDSEntity() : m_State(EEntityState::NOT_INITIALIZED) {} // Initialiser l'�tat � Uninitialized lors de la cr�ation de l'objet

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
	EEntityType m_Type = EEntityType::NONE; //Type de l'entit�

protected:
	EEntityState m_State; // �tat actuel de l'entit�

	dds_entity_t m_Entity;
};