#pragma once

#include "Core/DDSEntity.h"
#include "Participant/DDSParticipant.h"

#include "MorseEngineSubsystem.h"

 /**
  * @brief TODO
  * NOT USED
  */
 class MORSE_API MRSExecutor
{
public:

    MRSExecutor();
    ~MRSExecutor();

    dds_entity_t m_Waitset;

    void Init(UDDSParticipant* Participant)
    {
        m_Waitset = dds_create_waitset(Participant->GetEntity());
    };

    void Fini()
    {
        UMorseEngineSubsystem* MorseSubsystem = UMorseEngineSubsystem::Get();

    };

    void Spin()
    {
        (void)dds_waitset_wait(m_Waitset, NULL, 0, DDS_INFINITY);

        for (auto Entity : m_pEntities)
        {
            (void)dds_waitset_attach(m_Waitset, Entity->GetEntity(), 0);

            switch (Entity->GetType())
            {
            case EEntityType::PUBLISHER:
                // Traitement pour les entit�s de type Publisher
                break;

            case EEntityType::SUBSCRIBER:
                // Traitement pour les entit�s de type Subscriber
                break;

            case EEntityType::READER:
                // Traitement pour les entit�s de type Reader
                break;

            case EEntityType::WRITER:
                // Traitement pour les entit�s de type Writer
                break;

            case EEntityType::READ_CONDITION:
                // Traitement pour les entit�s de type Read Condition
                break;

            case EEntityType::TOPIC:
                // Traitement pour les entit�s de type Topic
                break;

            case EEntityType::NONE:
                // Traitement pour les entit�s de type NONE
                break;

            default:
                // Gestion d'un cas non pr�vu
                break;
            };
        };
    };

    TArray<UDDSEntity*> m_pEntities;
};