/*****************************************************************
 * @file   DDSQoS.h
 * @brief  This file contains Tools for definied Custom Data Model in Unreal Engine.
 * 
 * @author Nicolas B.
 * @date   March 2024
 * @copyright 2023 NicoBrugie. All rights reserved.
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "ddsc/dds.h"
#include "QoS/DDSQoSDataModel.h"

/**
 * @brief Default QoS configuration for sensors
 */ 
inline FQoSInfo QOS_DEFAULT_SENSOR = FQoSInfo{
	FQoSDurability{EQosDurability::TRANSIENT_LOCAL, 1},				
	FQoSHistory{EQosHistory::KEEP_LAST, 10},							// Keep last 10 samples
	FQoSReliability{EQosReliability::RELIABLE, 1000000},	// Max blocking time of 1ms
	FQoSLiveness{EQosLiveness::AUTOMATIC, 2000000000},		// 2 seconds lease duration
	FQoSOwnership{EQosOwnership::SYSTEM_DEFAULT, 1},
	FQoSConsistency{EQosConsistency::SYSTEM_DEFAULT,false, false,false,false}
};

/**
 * @brief Default QoS configuration high frequency topics
 */ 
inline FQoSInfo QOS_DEFAULT_HIGH_FREQUENCY = FQoSInfo{
	FQoSDurability{EQosDurability::VOLATILE, 1},						// Volatile data
	FQoSHistory{EQosHistory::KEEP_ALL, 0},							// Keep all samples
	FQoSReliability{EQosReliability::BEST_EFFORT, 0},		// No blocking
	FQoSLiveness{EQosLiveness::MANUAL_BY_TOPIC, 1000000000},	// 1 second lease duration
	FQoSOwnership{EQosOwnership::SYSTEM_DEFAULT, 1},
	FQoSConsistency{EQosConsistency::SYSTEM_DEFAULT,false, false,false,false}
};

class MORSE_API QoSUtils
{
public:

    static void SetQos(const FQoSInfo InQoS, dds_qos_t& OutQoS)
    {
        /** ----- HISTORY ----- */
        dds_history_kind_t HistoryKind  = DDS_HISTORY_KEEP_LAST; //DEFAULT
        switch (InQoS.History.Kind)
        {
        case EQosHistory::KEEP_LAST:
            HistoryKind = DDS_HISTORY_KEEP_LAST;
            break;
        case EQosHistory::KEEP_ALL:
            HistoryKind = DDS_HISTORY_KEEP_ALL;
            break;
        case EQosHistory::SYSTEM_DEFAULT:
            HistoryKind = DDS_HISTORY_KEEP_LAST;
            break;
        default:
            break;
        };
        dds_qset_history(&OutQoS, HistoryKind, InQoS.History.Depth);
    	
        /** ----- RELIABILITY ----- */
        dds_reliability_kind_t ReliabilityKind = DDS_RELIABILITY_BEST_EFFORT; //DEFAULT
        switch (InQoS.Reliability.Kind)
        {
        case EQosReliability::BEST_EFFORT:
            ReliabilityKind = DDS_RELIABILITY_BEST_EFFORT;
            break;
        case EQosReliability::RELIABLE:
            ReliabilityKind = DDS_RELIABILITY_RELIABLE;
            break;
        case EQosReliability::SYSTEM_DEFAULT:
            ReliabilityKind = DDS_RELIABILITY_RELIABLE;
            break;
        default:
            break;
        };
        dds_qset_reliability(&OutQoS, ReliabilityKind, InQoS.Reliability.MaxBlockingTime);

        /** ----- DURABILITY ----- */
        dds_durability_kind_t DurabilityKind = DDS_DURABILITY_TRANSIENT_LOCAL; //DEFAULT
        switch (InQoS.Durability.Kind)
        {
        case EQosDurability::VOLATILE:
            DurabilityKind = DDS_DURABILITY_VOLATILE;
            break;
        case EQosDurability::TRANSIENT_LOCAL:
            DurabilityKind = DDS_DURABILITY_TRANSIENT_LOCAL;
            break;
        case EQosDurability::TRANSIENT:
            DurabilityKind = DDS_DURABILITY_TRANSIENT;
            break;
        case EQosDurability::PERSISTENT:
            DurabilityKind = DDS_DURABILITY_PERSISTENT;
            break;
        case EQosDurability::SYSTEM_DEFAULT:
            DurabilityKind = DDS_DURABILITY_TRANSIENT_LOCAL;
            break;
        default:
            break;
        }
        dds_qset_durability(&OutQoS, DurabilityKind);

        /** ----- LIVENESS ----- */
        dds_liveliness_kind_t LivenessKind = DDS_LIVELINESS_MANUAL_BY_TOPIC; //DEFAULT
        switch (InQoS.Liveness.Kind)
        {
        case EQosLiveness::AUTOMATIC:
            LivenessKind = DDS_LIVELINESS_AUTOMATIC;
            break;
        case EQosLiveness::MANUAL_BY_TOPIC:
            LivenessKind = DDS_LIVELINESS_MANUAL_BY_TOPIC;
            break;
        case EQosLiveness::MANUAL_BY_PARTICIPANT:
            LivenessKind = DDS_LIVELINESS_MANUAL_BY_PARTICIPANT;
            break;
        case EQosLiveness::SYSTEM_DEFAULT:
            LivenessKind = DDS_LIVELINESS_AUTOMATIC;
            break;
        default:
            break;
        };
    	dds_qset_liveliness(&OutQoS, LivenessKind, InQoS.Liveness.LeaseDuration);
    	
    	/** ----- OWNERSHIP ----- */
    	dds_ownership_kind OwnershipKind = DDS_OWNERSHIP_SHARED; //DEFAULT
    	switch (InQoS.OwnerShip.Kind)
    	{
    	case EQosOwnership::SHARED:
    		OwnershipKind = DDS_OWNERSHIP_SHARED;
    		break;
    	case EQosOwnership::EXCLUSIVE:
    		OwnershipKind = DDS_OWNERSHIP_EXCLUSIVE;
    		break;
    	case EQosOwnership::SYSTEM_DEFAULT:
    		OwnershipKind = DDS_OWNERSHIP_SHARED;
    		break;
    	default:
    		break;
    	};
    	dds_qset_ownership(&OutQoS, OwnershipKind);
    	dds_qset_ownership_strength(&OutQoS, InQoS.OwnerShip.Strength);

    	/** ----- CONSISTENCY ----- */
    	dds_type_consistency_kind_t ConsistencyKind = DDS_TYPE_CONSISTENCY_ALLOW_TYPE_COERCION; //DEFAULT
    	switch (InQoS.Consistency.Kind)
    	{
    	case EQosConsistency::ALLOW_TYPE_COERCION:
    		ConsistencyKind = DDS_TYPE_CONSISTENCY_ALLOW_TYPE_COERCION;
    		break;
    	case EQosConsistency::DISALLOW_TYPE_COERCION:
    		ConsistencyKind = DDS_TYPE_CONSISTENCY_DISALLOW_TYPE_COERCION;
    		break;
    	case EQosConsistency::SYSTEM_DEFAULT:
    		ConsistencyKind = DDS_TYPE_CONSISTENCY_DISALLOW_TYPE_COERCION;
    		break;
    	default:
    		break;
    	};
    	dds_qset_type_consistency(
    		&OutQoS,
    		ConsistencyKind,
    		InQoS.Consistency.IgnoreSequenceBounds,
    		InQoS.Consistency.IgnoreStringBounds,
    		InQoS.Consistency.IgnoreMemberNames,
    		InQoS.Consistency.PreventTypeWidening,
    		InQoS.Consistency.ForceTypeValidation
    		);
    	
    	/** ----- DATA REPRESENTATION ----- TODO : Allow CDR representation in qos settings */
        dds_qset_data_representation(&OutQoS, 0, DDS_DATA_REPRESENTATION_XCDR1);
    };
};