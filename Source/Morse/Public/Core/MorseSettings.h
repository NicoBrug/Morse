// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ddsc/dds.h"
#include "MorseSettings.generated.h"

UENUM(BlueprintType)
enum class EDDSVerbosity : uint8
{
	None UMETA(DisplayName = "None"),              // no Cyclone DDS log
	Severe UMETA(DisplayName = "Severe"),          // error and fatal
	Warning UMETA(DisplayName = "Warning"),        // severe + warning
	Info UMETA(DisplayName = "Info"),              // warning + info
	Config UMETA(DisplayName = "Config"),          // info + config
	Fine UMETA(DisplayName = "Fine"),              // config + discovery
	Finer UMETA(DisplayName = "Finer"),            // fine + traffic and timing
	Finest UMETA(DisplayName = "Finest")           // finer + trace
};

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="DDS Settings"))
class MORSE_API UMorseSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "DDS Configuration")
	FString DDSDomainConfigPath;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "DDS Configuration")
	bool OverrideDDSXmlConf = true;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "DDS Configuration")
	int DomainId = DDS_DOMAIN_DEFAULT;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "DDS Configuration", meta = (EditCondition = "OverrideDDSXmlConf"))
	EDDSVerbosity LogsVerbosity = EDDSVerbosity::Info;
};
