// Fill out your copyright notice in the Description page of Project Settings.


#include "DDS/Entity/DDSDomain.h"

#include "XmlFile.h"
#include "Core/MRSSettings.h"
#include "Utils/MRSLogs.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"
#include "HAL/FileManager.h"

void FDDSDomain::Initialize()
{
	UMRSSettings* Settings = GetMutableDefault<UMRSSettings>();

	dds_domainid_t DomainId = Settings->DomainId;
	bool UseConfigurationFile = Settings->OverrideDDSXmlConf;

	FString XmlConfig;
	
	if(!LoadXmlDomainConfig(Settings->DDSDomainConfigPath, XmlConfig)) 
	{
		UE_LOGFMT(LogTemp, Warning, "Can't load DDS XML Configuration file : Path {0}, check XML validity", *Settings->DDSDomainConfigPath);
	};
	
	auto XmlConfigAnsi = StringCast<ANSICHAR>(*XmlConfig);
	const char* XmlConfigChar = XmlConfigAnsi.Get();
	
	EntityHandler = dds_create_domain(0, XmlConfigChar);

	if (EntityHandler < 0)
	{
		UE_LOGFMT(LogTemp, Warning, "Can't create DDS Domain with Config {0}", *XmlConfigChar);
		SetState(EEntityState::NOT_INITIALIZED);
		return;
	};

	SetState(EEntityState::INITIALIZED);
};

void FDDSDomain::Terminate()
{
	RC_DDS_CHECK(dds_delete(EntityHandler)); //DDS Check return code
	SetState(EEntityState::DESTROYED);
}

dds_domainid_t FDDSDomain::GetDomainId() const
{
	dds_domainid_t OutId = 0;
	RC_DDS_CHECK(dds_get_domainid(EntityHandler, &OutId));
	return OutId;
};

bool FDDSDomain::LoadXmlDomainConfig(FString Path, FString& OutXml)
{
	UMRSSettings* Settings = GetMutableDefault<UMRSSettings>();

	if (!FPaths::FileExists(Path))
	{
		UE_LOG(LogTemp, Error, TEXT("Le fichier XML spécifié n'existe pas : %s"), *Path);
		return false;
	}

	FXmlFile XmlFile;
	if (!XmlFile.LoadFile(Path, EConstructMethod::Type::ConstructFromFile))
	{
		UE_LOG(LogTemp, Error, TEXT("Impossible de charger le fichier XML : %s"), *Path);
		UE_LOG(LogTemp, Error, TEXT("Erreur : %s"), *XmlFile.GetLastError());
		return false;
	}
	
	FXmlNode* RootNode = XmlFile.GetRootNode();
	if (!RootNode)
	{
		UE_LOG(LogTemp, Error, TEXT("Le fichier XML ne contient pas de nœud racine valide."));
		return false;
	}

	if(!Settings->OverrideDDSXmlConf)
	{
		OutXml = SerializeXmlNodeToString(RootNode,0);
		return true;
	};
	
	FXmlNode* DomainNode = RootNode->FindChildNode("Domain");
	if (!DomainNode)
	{
		UE_LOG(LogTemp, Error, TEXT("Le fichier XML ne contient pas de nœud Domain valide."));
		return false;
	};
	
	// ------- OVERRIDE PARAMETERS IN XML -------//
	FXmlNode* TracingNode = DomainNode->FindChildNode("Tracing");
	if (TracingNode)
	{
		FXmlNode* OutputFileNode = TracingNode->FindChildNode("OutputFile");
		if (OutputFileNode)
		{
			// Modifier la valeur de <OutputFile>
			FString NewOutputFilePath = GetLogFilePath();
			OutputFileNode->SetContent(GetLogFilePath());

			UE_LOG(LogTemp, Log, TEXT("Chemin <OutputFile> mis à jour : %s"), *NewOutputFilePath);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Balise <OutputFile> non trouvée dans <Tracing>."));
		};
		
		FXmlNode* VerbosityNode = TracingNode->FindChildNode("Verbosity");
		if (VerbosityNode)
		{
			// Modifier la valeur de <OutputFile>
			FString NewVerbosity = UEnum::GetValueAsString(Settings->LogsVerbosity);
			OutputFileNode->SetContent(GetLogFilePath());

			UE_LOG(LogTemp, Log, TEXT("Verbosité <Verbosity> mis à jour : %s"), *NewVerbosity);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Balise <Verbosity> non trouvée dans <Tracing>."));
		};
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Balise <Tracing> non trouvée."));
	}

	// Exporter le contenu XML mis à jour dans OutXml
	OutXml = SerializeXmlNodeToString(RootNode,0);
	return true;
}

FString FDDSDomain::SerializeXmlNodeToString(FXmlNode* Node, int32 IndentLevel)
{
		if (!Node) return FString();

		FString Indent = FString::ChrN(IndentLevel, TEXT('\t'));
		FString XmlContent;

		// Ajouter l'ouverture du tag
		XmlContent += Indent + FString::Printf(TEXT("<%s"), *Node->GetTag());

		// Ajouter les attributs
		for (const auto& Attribute : Node->GetAttributes())
		{
			XmlContent += FString::Printf(TEXT(" %s=\"%s\""), *Attribute.GetTag(), *Attribute.GetValue());
		}

		// Vérifier s'il y a du contenu ou des enfants
		const TArray<FXmlNode*>& Children = Node->GetChildrenNodes();
		if (Children.Num() > 0 || !Node->GetContent().IsEmpty())
		{
			XmlContent += TEXT(">\n");

			// Ajouter le contenu si présent
			if (!Node->GetContent().IsEmpty())
			{
				XmlContent += Indent + TEXT("\t") + Node->GetContent() + TEXT("\n");
			}

			// Ajouter les enfants
			for (FXmlNode* ChildNode : Children)
			{
				XmlContent += SerializeXmlNodeToString(ChildNode, IndentLevel + 1);
			}

			// Fermer le tag
			XmlContent += Indent + FString::Printf(TEXT("</%s>\n"), *Node->GetTag());
		}
		else
		{
			// Tag vide
			XmlContent += TEXT(" />\n");
		}

		return XmlContent;
}

bool FDDSDomain::CreateDirectoryIfNotExists(const FString& DirectoryPath)
{
	// Accéder au gestionnaire de fichiers
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	// Vérifier si le répertoire existe déjà
	if (!PlatformFile.DirectoryExists(*DirectoryPath))
	{
		// Essayer de créer le répertoire (y compris les sous-dossiers)
		return PlatformFile.CreateDirectoryTree(*DirectoryPath);
	}
	return true;
}

FString FDDSDomain::GetLogFilePath()
{
	// Construire le chemin sans le fichier
	FString DirectoryPath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("LogsDDS"));

	// Vérifier et créer les sous-dossiers si nécessaire
	if (!CreateDirectoryIfNotExists(DirectoryPath))
	{
		UE_LOG(LogTemp, Error, TEXT("Impossible de créer le répertoire : %s"), *DirectoryPath);
		return FString();
	}

	FString Timestamp = FDateTime::Now().ToString(TEXT("%Y-%m-%d_%H-%M-%S"));
	// Ajouter le nom du fichier
	FString LogFilePath = FPaths::Combine(DirectoryPath, FString::Printf(TEXT("Morse.%s.${CYCLONEDDS_PID}.log"), *Timestamp));
	return LogFilePath;
};
