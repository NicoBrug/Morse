/*****************************************************************
 * @file   MRSExecutor.h
 * @brief  /
 * 
 * @author Nicolas B.
 * @date   March 2024
 * @copyright Copyright 2025 NicoBrugie. All rights reserved.
 *********************************************************************/
#pragma once

#include "MRSBaseThread.h"
#include "DDS/Entity/DDSEntity.h"
#include "DDS/Entity/DDSParticipant.h"
#include "Utils/MRSLogs.h"

class MORSE_API MRSThreadedExecutor : public MRSThreadBase
{
public:

	typedef MRSThreadBase Super;

	MRSThreadedExecutor(const FTimespan& InThreadTickRate, const TCHAR* InName);
	virtual ~MRSThreadedExecutor();
	
	virtual void ThreadTick(double dDeltaTime) override;
 
    void Init(UDDSParticipant* Participant);
 	void AddEntity(UDDSEntity* Entity);
    void Execute();
 
 private :
	
	bool IsRunning;
	bool ShouldStop = false;
	TSet<dds_attach_t> AttachedEntities;
	dds_entity_t WaitsetHandler;
	TArray<UDDSEntity*> m_pEntities;

	/** -------- ENTITY HANDLERS BEGIN -------- */
 	void HandleEntity(UDDSEntity* Entity);
 	void HandleReader(UDDSEntity* Entity);
	/** -------- ENTITY HANDLERS END -------- */
	
	/** -------- WAITSET OPERATIONS BEGIN -------- */
	void AttachEntitiesToWaitset();
	void AttachEntityToWaitset(UDDSEntity* Entity);
	void DetachEntityFromWaitset(UDDSEntity* Entity);
	void DetachAllEntitiesFromWaitset();
	/** -------- WAITSET OPERATIONS END -------- */
};