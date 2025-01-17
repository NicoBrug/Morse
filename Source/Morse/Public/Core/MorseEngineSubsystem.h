/*****************************************************************//**
 * @file   MorseEngineSubsystem.h
 * @brief  /
 * 
 * @author Nicolas B.
 * @date   March 2024
 * @copyright Copyright 2023 NicoBrugie. All rights reserved.
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"

#include "Participant/DDSParticipant.h"
#include <Topic/DDSTopic.h>
#include <Topic/DDSReader.h>
#include <Topic/DDSWriter.h>
#include <Topic/TopicProxy.h>
#include <Utils/MRSLogs.h>

#include "Kismet/GameplayStatics.h"
#include "QoS/DDSQoS.h"

#include "MorseEngineSubsystem.generated.h"


USTRUCT(BlueprintType)
struct FTopicDescription
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic", meta=(DisplayName="Quality Of Service"))
    FQoSInfo QualityOfService;

    void SetName(const FString& InName)
    {
        Name = InName;
    };
    
    void SetQualityOfService(const FQoSInfo& QosInfo)
    {
        QualityOfService = QosInfo;
    };
};

/**
 * 
 */
UCLASS()
class MORSE_API UMorseEngineSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    static UMorseEngineSubsystem* Get()
    {
        UWorld* pWorld = (GEngine && GEngine->GameViewport) ? GEngine->GameViewport->GetWorld() : nullptr;

        if (!pWorld)
        {
            UE_LOGFMT(LogMorse, Error, "UMorseEngineSubsystem::Get : Impossible de recuperer une instance du World");
            return nullptr;
        }

        UGameInstance* pGI = UGameplayStatics::GetGameInstance(pWorld);

        if (!pGI)
        {
            UE_LOGFMT(LogMorse, Error, "UMorseEngineSubsystem : Impossible de recuperer le Game Instance");
            return nullptr;
        }

        return pGI->GetSubsystem<UMorseEngineSubsystem>();
    };

    void OnPostWorldInit(UWorld* pWorld, const UWorld::InitializationValues);
    
    /**
     * @brief Operation wich return the default morse participant.
     * 
     * @return 
     */
    UFUNCTION(BlueprintPure, BlueprintCallable)
    UDDSParticipant* GetDefaultParticipant();
   
private:

    UPROPERTY()
    UDDSParticipant* DefaultParticipant; //default participant of morse, ALL the entity will be created with this participant
};
