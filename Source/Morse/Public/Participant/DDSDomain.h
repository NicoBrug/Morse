// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Core/DDSEntity.h"

class FXmlNode;

class MORSE_API FDDSDomain : public UDDSEntity
{
public:
	FDDSDomain(){SetType(EEntityType::DDS_DOMAIN);};
	~FDDSDomain(){};
	virtual void Initialize() override;
	virtual void Terminate() override;

	dds_domainid_t GetDomainId() const;
	
private :
	bool LoadXmlDomainConfig(FString Path, FString& OutXml);
	FString SerializeXmlNodeToString(FXmlNode* Node, int32 IndentLevel /*= 0*/);
	bool CreateDirectoryIfNotExists(const FString& DirectoryPath);
	FString GetLogFilePath();
};
