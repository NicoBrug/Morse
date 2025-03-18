#include "Core/MRSSubsystem.h"
#include "Engine/World.h"
#include "Core/MRSExecutor.h"

#include "Core/MRSSettings.h"

void UMorseSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UMorseSubsystem::OnPostWorldInit);
};

void UMorseSubsystem::Deinitialize()
{
	if(DefaultParticipant)
	{
		DefaultParticipant->Terminate();
	}
}

UMorseSubsystem* UMorseSubsystem::Get()
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

	return pGI->GetSubsystem<UMorseSubsystem>();
}

void UMorseSubsystem::OnPostWorldInit(UWorld* pWorld, const UWorld::InitializationValues)
{
	DefaultParticipant = NewObject<UDDSParticipant>(this);
	DefaultParticipant->Initialize();

	const FTimespan ThreadWaitTime = FTimespan::FromMilliseconds(10);  
	const FString UniqueServerName = "MorseExecutor";

	Executor = MakeShared<MRSThreadedExecutor>(ThreadWaitTime, *UniqueServerName);
	Executor->Init(DefaultParticipant);
};

UDDSParticipant* UMorseSubsystem::GetDefaultParticipant()
{
    return DefaultParticipant;
};