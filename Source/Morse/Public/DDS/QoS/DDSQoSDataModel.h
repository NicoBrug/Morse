/*****************************************************************
* @file   DDSQoSDataModel.h
 * @brief  This file contains the implementation of the definitions of the different QoS according to DDS Specificication
 * QoS : https://fast-dds.docs.eprosima.com/en/latest/fastdds/dds_layer/core/policy/standardQosPolicies.html
 * 
 * @author Nicolas B.
 * @date   March 2024
 * @copyright 2023 NicoBrugie. All rights reserved.
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DDSQoSDataModel.generated.h"


/**
 * @defgroup QoS Quality of Service Policies
 * @{
 * This group includes various QoS policies for DDS, defining how data is managed
 * and transmitted.
 */

/**
 * @brief Enum representing the History QoS policy options in DDS.
 * 
 * History determines how much data is stored for subscribers. It can either limit the amount of data or keep all data samples indefinitely.
 */
UENUM(BlueprintType)
enum class EQosHistory : uint8 {
	/**
	 * @brief System default history.
	 * 
	 * Uses the DDS system's default history policy, which may vary depending on the configuration.
	 */
	SYSTEM_DEFAULT  UMETA(DisplayName = "DDS_QOS_POLICY_HISTORY_SYSTEM_DEFAULT"),

	/**
	 * @brief Keep last N samples.
	 * 
	 * Only the last N data samples are kept. The value of N is typically configurable, and older samples are discarded.
	 */
	KEEP_LAST       UMETA(DisplayName = "DDS_QOS_POLICY_HISTORY_KEEP_LAST"),

	/**
	 * @brief Keep all samples.
	 * 
	 * All data samples are stored and made available to subscribers. No data is discarded, allowing subscribers to access the full history.
	 */
	KEEP_ALL        UMETA(DisplayName = "DDS_QOS_POLICY_HISTORY_KEEP_ALL"),

	/**
	 * @brief Unknown history policy.
	 * 
	 * The history policy is not specified or is unknown, and it may depend on other settings.
	 */
	UNKNOWN         UMETA(DisplayName = "DDS_QOS_POLICY_HISTORY_UNKNOWN"),
};


/**
 * @brief Enum representing the Reliability QoS policy options in DDS.
 * 
 * Reliability controls the assurance of message delivery. It determines whether data must be delivered reliably or if occasional data loss is acceptable.
 */
UENUM(BlueprintType)
enum class EQosReliability : uint8 {
	/**
	 * @brief System default reliability.
	 * 
	 * Uses the system's default reliability policy.
	 */
	SYSTEM_DEFAULT   UMETA(DisplayName = "DDS_QOS_POLICY_RELIABILITY_SYSTEM_DEFAULT"),
	
	/**
	 * @brief Best effort reliability.
	 * 
	 * Data is delivered on a best-effort basis, meaning that the system will try to deliver messages, but occasional data loss is acceptable.
	 */
	BEST_EFFORT      UMETA(DisplayName = "DDS_QOS_POLICY_RELIABILITY_BEST_EFFORT"),

	/**
	 * @brief Reliable delivery.
	 * 
	 * All data is guaranteed to be delivered to subscribers. This ensures no data loss, but may introduce additional overhead for acknowledgment and retransmission.
	 */
	RELIABLE         UMETA(DisplayName = "DDS_QOS_POLICY_RELIABILITY_RELIABLE"),

	/**
	 * @brief Unknown reliability policy.
	 * 
	 * The reliability policy is unspecified or unknown, and it may depend on other settings.
	 */
	UNKNOWN          UMETA(DisplayName = "DDS_QOS_POLICY_RELIABILITY_UNKNOWN"),
};


/**
 * @brief Enum representing the Durability QoS policy options in DDS.
 * 
 * Durability defines how data is handled in terms of persistence.
 * It determines whether data is kept after publication for future subscribers.
 */
UENUM(BlueprintType)
enum class EQosDurability : uint8 {
	/**
	 * @brief System default durability.
	 * 
	 * Uses the system's default durability policy.
	 */
	SYSTEM_DEFAULT    UMETA(DisplayName = "DDS_DURABILITY_SYSTEM_DEFAULT"),
	
    /**
     * @brief Volatile durability.
     * 
     * Data is not stored after being published. Late-joining subscribers will not receive past messages.
     */
    VOLATILE          UMETA(DisplayName = "DDS_DURABILITY_VOLATILE"),

    /**
     * @brief Transient local durability.
     * 
     * Data is stored only in the local memory of the publisher. Late-joining subscribers will receive past messages as long as the publisher is still active.
     */
    TRANSIENT_LOCAL   UMETA(DisplayName = "DDS_DURABILITY_TRANSIENT_LOCAL"),

    /**
     * @brief Transient durability.
     * 
     * Data is stored across the network and will be available to late-joining subscribers even after the publisher has stopped. However, it is not persistently stored.
     */
    TRANSIENT         UMETA(DisplayName = "DDS_DURABILITY_TRANSIENT"),

    /**
     * @brief Persistent durability.
     * 
     * Data is stored persistently and remains available to late-joining subscribers even after the system is restarted. This ensures long-term availability of data.
     */
    PERSISTENT        UMETA(DisplayName = "DDS_DURABILITY_PERSISTENT"),

    /**
     * @brief Unknown durability.
     * 
     * The durability is unknown or unspecified. It may depend on other system settings.
     */
    UNKNOWN           UMETA(DisplayName = "DDS_DURABILITY_UNKNOWN"),
};


/**
 * @brief Enum representing the Liveness QoS policy options in DDS.
 * 
 * Liveness defines how the system ensures that participants (such as publishers) are still alive 
 * and actively communicating within the DDS network. It helps detect failures and manage the lifecycle of data.
 */
UENUM(BlueprintType)
enum class EQosLiveness : uint8 {
	/**
	 * @brief System default liveness.
	 * 
	 * Uses the default liveness policy as defined by the DDS system.
	 */
	SYSTEM_DEFAULT          UMETA(DisplayName = "DDS_QOS_POLICY_LIVELINESS_SYSTEM_DEFAULT"),

	/**
	 * @brief Automatic liveness.
	 * 
	 * The system automatically manages the liveness of participants. No explicit action is required from the participant to declare itself as alive.
	 */
	AUTOMATIC               UMETA(DisplayName = "DDS_QOS_POLICY_LIVELINESS_AUTOMATIC"),

	/**
	 * @brief Manual by topic liveness.
	 * 
	 * Liveness is managed manually by each topic. The participant must periodically assert its liveness for each topic it is publishing.
	 */
	MANUAL_BY_TOPIC         UMETA(DisplayName = "DDS_QOS_POLICY_LIVELINESS_MANUAL_BY_TOPIC"),

	/**
	 * @brief Manual by participant liveness.
	 * 
	 * Liveness is managed manually by the participant as a whole. The participant must explicitly assert its own liveness to remain active in the system.
	 */
	MANUAL_BY_PARTICIPANT   UMETA(DisplayName = "DDS_QOS_POLICY_LIVELINESS_MANUAL_BY_PARTICIPANT"),
};

/**
 * @brief Enum representing the Ownership QoS policy options in DDS.
 * 
 * The Ownership QoS policy defines how ownership of data samples is managed 
 * between DataWriters in a DDS system. It determines whether multiple 
 * DataWriters can share ownership of the same data (shared) or if 
 * ownership is exclusive to a single DataWriter.
 */
UENUM(BlueprintType)
enum class EQosOwnership : uint8
{
	/**
	 * @brief System default ownership.
	 * 
	 * Uses the default ownership policy as defined by the DDS system. 
	 */
	SYSTEM_DEFAULT          UMETA(DisplayName = "DDS_QOS_POLICY_OWNERSHIP_SYSTEM_DEFAULT"),

	/**
	 * @brief Shared ownership.
	 * 
	 * Allows multiple DataWriters to share ownership of the same data instance. 
	 * This enables collaborative data publishing, where data can be produced 
	 * by different sources while ensuring all owners can modify it.
	 */
	SHARED    UMETA(DisplayName = "DDS_QOS_POLICY_OWNERSHIP_SHARED"),

	/**
	 * @brief Exclusive ownership.
	 * 
	 * Grants ownership of a data instance to a single DataWriter. 
	 * Only the owner can modify or update the data, ensuring that 
	 * changes are made exclusively by the designated writer.
	 */
	EXCLUSIVE UMETA(DisplayName = "DDS_QOS_POLICY_OWNERSHIP_EXCLUSIVE")
};


/**
 * @brief Enum representing the Consistency QoS policy options in DDS.
 * 
 * The Consistency QoS policy defines how type coercion is handled 
 * during data communication in DDS. It determines whether 
 * the system allows or disallows the automatic conversion 
 * of data types between DataWriters and DataReaders.
 */
UENUM(BlueprintType)
enum class EQosConsistency : uint8
{
	/**
	 * @brief System default Consistency
	 * 
	 * Uses the default ownership policy as defined by the DDS system. 
	 */
	SYSTEM_DEFAULT          UMETA(DisplayName = "DDS_QOS_POLICY_OWNERSHIP_SYSTEM_DEFAULT"),
	
	/**
	 * @brief Allow type coercion.
	 * 
	 * This option permits the automatic conversion of data types 
	 * between DataWriters and DataReaders. It enables more flexible 
	 * communication, as DataReaders can accept data that may not 
	 * exactly match their expected type.
	 */
	ALLOW_TYPE_COERCION UMETA(DisplayName = "DDS_TYPE_CONSISTENCY_ALLOW_TYPE_COERCION"),

	/**
	 * @brief Disallow type coercion.
	 * 
	 * This option prohibits automatic type conversion during 
	 * data transmission. DataReaders must receive data that 
	 * exactly matches their expected type, ensuring strict type 
	 * safety and consistency.
	 */
	DISALLOW_TYPE_COERCION UMETA(DisplayName = "DDS_TYPE_CONSISTENCY_DISALLOW_TYPE_COERCION")
};


/**
 * @brief Structure defining the History QoS policy in DDS.
 * 
 * The History QoS policy controls how samples are stored and made available to DataReaders.
 * It determines whether only a limited number of recent samples are kept, or if all samples 
 * are stored. This policy impacts the amount of memory used and how data is handled when 
 * DataReaders fall behind the DataWriter.
 */
USTRUCT(BlueprintType)
struct FQoSHistory
{
	GENERATED_BODY()

public:
	/**
	 * @brief Specifies the history kind.
	 * 
	 * The kind defines the history behavior for data. With `KEEP_LAST`, only the last N samples 
	 * (as specified by the Depth) are kept. Older samples are discarded once the limit is reached. 
	 * With `KEEP_ALL`, all samples are stored, allowing DataReaders to access the complete history of data.
	 * 
	 * Default: SYSTEM_DEFAULT.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQosHistory Kind = EQosHistory::SYSTEM_DEFAULT;

	/**
	 * @brief Depth of the history.
	 * 
	 * Specifies how many samples to retain in memory. This setting is relevant when `Kind` is set to `KEEP_LAST`, 
	 * as it defines how many of the most recent samples are stored. The depth value is applied per instance 
	 * (for keyed Topics). A higher depth allows more data to be buffered, but consumes more memory.
	 * 
	 * Unit: Number of samples.
	 * Default: 1.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Depth = 1;
};


/**
 * @brief Structure defining the Reliability QoS policy in DDS.
 * 
 * The Reliability QoS policy controls the level of guarantee that data sent from a DataWriter 
 * will be received by a DataReader. It determines whether data transmission should be 
 * guaranteed (reliable) or if some data loss is acceptable (best effort).
 */
USTRUCT(BlueprintType)
struct FQoSReliability
{
	GENERATED_BODY()

public:

	/**
	 * @brief Specifies the reliability kind.
	 * 
	 * The reliability kind determines whether data transmission is guaranteed. 
	 * With `BEST_EFFORT`, the system does not guarantee delivery, and messages may be lost. 
	 * With `RELIABLE`, every sample is guaranteed to be delivered to all matching DataReaders, 
	 * using acknowledgment and retransmission mechanisms if needed.
	 * 
	 * Default: SYSTEM_DEFAULT.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQosReliability Kind = EQosReliability::SYSTEM_DEFAULT;

	/**
	 * @brief Maximum blocking time for reliable delivery.
	 * 
	 * This property defines the maximum time the DataWriter is allowed to block while waiting 
	 * for acknowledgments from DataReaders during reliable communication. If acknowledgments 
	 * are not received within this time, the system may consider the delivery failed.
	 * 
	 * Unit: Nanoseconds.
	 * Default: 1 nanosecond.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxBlockingTime = 1;
};


/**
 * @brief Structure defining the Durability QoS policy in DDS.
 * 
 * The Durability QoS policy controls the persistence of data beyond the lifetime of DataReaders. 
 * It determines whether data remains available for late-joining DataReaders or if it is only 
 * available to currently active subscribers.
 */
USTRUCT(BlueprintType)
struct FQoSDurability
{
	GENERATED_BODY()

public:

	/**
	 * @brief Specifies the durability kind.
	 * 
	 * The durability kind determines whether data persists after it is written. 
	 * With `VOLATILE`,  data is not stored after beingsent, meaning late-joining DataReaders 
	 * will not receive past samples. With `TRANSIENT_LOCAL`, data is stored temporarily and 
	 * made available to late-joining subscribers while the DataWriter remains active.
	 * 
	 * Default: SYSTEM_DEFAULT.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQosDurability Kind = EQosDurability::SYSTEM_DEFAULT;

	/**
	 * @brief Depth of durability.
	 * 
	 * Defines how many samples are stored by the system for future DataReaders. This is relevant 
	 * for durability settings that involve data persistence, such as `TRANSIENT_LOCAL` or `PERSISTENT`. 
	 * A higher depth allows more historical data to be available to late subscribers, but increases 
	 * memory usage.
	 * 
	 * Unit: Number of samples.
	 * Default: 1.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Depth = 1;
};


/**
 * @brief Structure defining the Liveliness QoS policy in DDS.
 * @ingroup QoS
 * The Liveliness QoS policy ensures that participants and writers regularly assert their liveliness status 
 * to the DDS system, preventing stale data from inactive entities. It controls how often entities must notify 
 * that they are still alive, which allows the system to detect failures or disconnections.
 */
USTRUCT(BlueprintType)
struct FQoSLiveness
{
	GENERATED_BODY()

public:
	/**
	 * @brief Specifies the liveliness kind.
	 * 
	 * The liveliness kind defines how a participant or DataWriter maintains its liveliness status. 
	 * Options include `AUTOMATIC`, where the system manages liveliness, and `MANUAL`, 
	 * where the participant or writer must explicitly assert its liveliness.
	 * 
	 * Default: SYSTEM_DEFAULT.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQosLiveness Kind = EQosLiveness::SYSTEM_DEFAULT;

	/**
	 * @brief Lease duration for liveliness.
	 * 
	 * Specifies the duration in nanoseconds that a remote DomainParticipant considers the local 
	 * DomainParticipant or DataWriter to be alive without receiving any further liveliness assertions. 
	 * If no assertions are made within this duration, the entity is considered inactive.
	 * 
	 * Unit: Nanoseconds.
	 * Default: 1 second (1000000000 nanoseconds).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 LeaseDuration = 9223372036854775807;
};

/**
 * @brief Structure defining the Ownership QoS policy in DDS.
 * 
 * The Ownership QoS policy manages how ownership of data samples is handled 
 * within the DDS system, determining whether ownership is shared among multiple 
 * DataWriters or exclusive to a single DataWriter.
 */
USTRUCT(BlueprintType)
struct FQoSOwnership
{
	GENERATED_BODY()

public:
	/**
	 * @brief Specifies the ownership kind.
	 * 
	 * The ownership kind defines the policy for managing data ownership in DDS. 
	 * Options include `SYSTEM_DEFAULT`, `SHARED` (allowing multiple DataWriters 
	 * to share ownership), and `EXCLUSIVE` (granting ownership to a single DataWriter).
	 * 
	 * Default: SYSTEM_DEFAULT.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQosOwnership Kind = EQosOwnership::SYSTEM_DEFAULT;

	/**
	 * @brief Strength of ownership.
	 * 
	 * This property defines the strength of the ownership policy when multiple 
	 * DataWriters are sharing ownership. It can be used to determine how conflicts 
	 * are resolved when there are competing updates from different writers. 
	 * Higher values may indicate stronger control or priority for a specific writer.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Strength;
};

/**
 * @brief Structure defining the Consistency QoS policy in DDS.
 * 
 * The Consistency QoS policy controls how type coercion and data validation 
 * are handled during communication between DataWriters and DataReaders. 
 * It specifies whether certain types of data mismatches should be ignored 
 * or strictly enforced, ensuring data integrity and type safety.
 */
USTRUCT(BlueprintType)
struct FQoSConsistency
{
    GENERATED_BODY()

public:
    /**
     * @brief Specifies the consistency kind.
     * 
     * The consistency kind defines how type coercion is managed in DDS. 
     * Options include `ALLOW_TYPE_COERCION` (which permits automatic type 
     * conversion) and `DISALLOW_TYPE_COERCION` (which enforces strict type 
     * matching).
     * 
     * Default: SYSTEM_DEFAULT.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EQosConsistency Kind = EQosConsistency::SYSTEM_DEFAULT;

    /**
     * @brief Ignore sequence bounds.
     * 
     * When set to true, the system will ignore bounds on sequences, 
     * allowing DataReaders to accept sequences that exceed their 
     * predefined limits.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool IgnoreSequenceBounds = false;

    /**
     * @brief Ignore string bounds.
     * 
     * When set to true, the system will ignore bounds on strings, 
     * permitting DataReaders to accept strings longer than their 
     * expected size.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool IgnoreStringBounds = false;

    /**
     * @brief Ignore member names.
     * 
     * When set to true, the system will ignore the names of members 
     * in structured data types, allowing for greater flexibility 
     * in data handling.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool IgnoreMemberNames = false;

    /**
     * @brief Prevent type widening.
     * 
     * When set to true, the system will enforce strict type safety 
     * by preventing type widening, which could lead to potential data 
     * loss or inconsistencies.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool PreventTypeWidening = false;

    /**
     * @brief Force type validation.
     * 
     * When set to true, the system will strictly enforce type validation, 
     * ensuring that all data matches the expected types exactly.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool ForceTypeValidation = false;
};

/** @} */ // End of QoS group

/**
 * @brief Structure aggregating various QoS (Quality of Service) policies in DDS.
 * 
 * The `FQoSInfo` structure groups several QoS policies that control the behavior of data communication in DDS. 
 * These policies define how data is delivered, stored, and managed, providing flexibility in configuring 
 * communication reliability, durability, liveliness, and history.
 */
USTRUCT(BlueprintType)
struct FQoSInfo
{
    GENERATED_BODY()

public:

    /**
     * @brief Durability QoS policy.
     * 
     * The Durability QoS policy specifies whether data persists for future subscribers.
     * It determines if data is only available to current DataReaders (`VOLATILE`) 
     * or if it persists for late-joining readers (`TRANSIENT_LOCAL` or `PERSISTENT`).
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FQoSDurability Durability;

    /**
     * @brief History QoS policy.
     * 
     * The History QoS policy controls how data is stored for subscribers. 
     * It determines whether only the last N samples (`KEEP_LAST`) or all samples (`KEEP_ALL`) 
     * are retained, and how many samples are stored for each instance of data.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FQoSHistory History;

    /**
     * @brief Reliability QoS policy.
     * 
     * The Reliability QoS policy defines how data is transmitted between DataWriters and DataReaders. 
     * Options include `BEST_EFFORT` (where some data loss is acceptable) and `RELIABLE` 
     * (which ensures guaranteed delivery of data with retransmission if necessary).
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FQoSReliability Reliability;

    /**
     * @brief Liveliness QoS policy.
     * 
     * The Liveliness QoS policy determines how the system detects whether entities such as DataWriters 
     * are still alive. It specifies how often a participant must assert its liveliness and the time 
     * (lease duration) after which an inactive entity is considered dead.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FQoSLiveness Liveness;

	/**
	 * @brief Ownership QoS policy.
	 * 
	 * The Ownership QoS policy defines how ownership of data samples is managed 
	 * between DataWriters. It specifies whether multiple DataWriters can share 
	 * ownership of the same data instance (`SHARED`) or if ownership is exclusive 
	 * to a single DataWriter (`EXCLUSIVE`).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQoSOwnership OwnerShip;

	/**
	 * @brief Consistency QoS policy.
	 * 
	 * The Consistency QoS policy defines how type coercion and data validation 
	 * are managed during communication between DataWriters and DataReaders. 
	 * This policy specifies whether the system allows type coercion, as well as 
	 * other validation options regarding sequence bounds, string bounds, 
	 * member names, type widening, and strict type validation. 
	 * Proper configuration of this property ensures data integrity and 
	 * adherence to expected data formats during transmission.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQoSConsistency Consistency;
};