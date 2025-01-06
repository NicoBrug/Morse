/*****************************************************************
 * @file   DDSParticipant.h
 * @brief  This file contains the implementation of the a DDS Domain participant.
 * DDS Domain participant : https://fast-dds.docs.eprosima.com/en/latest/fastdds/dds_layer/domain/domainParticipant/domainParticipant.html#dds-layer-domainparticipant
 * 
 * @author Nicolas B.
 * @date   March 2024
 * @copyright 2023 NicoBrugie. All rights reserved.
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/DDSEntity.h"
#include "DDSParticipant.generated.h"





/**
 * 
 */
UCLASS()
class MORSE_API UDDSParticipant : public UObject, public UDDSEntity
{
	GENERATED_BODY()
	
public :

	UDDSParticipant(const FObjectInitializer& Initializer);

	virtual void Initialize() override;
	virtual void Terminate() override;
};
