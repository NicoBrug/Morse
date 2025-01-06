/*****************************************************************
* @file   MRSLogs.h
 * @brief   This file contains all code related to custom Logs. (DDS Error Mapping, Custom Logs etc)
 * 
 * @author Nicolas B.
 * @date   March 2024
 * @copyright Nicolas Brugie. All rights reserved.
 *********************************************************************/
#pragma once

#include <Runtime/Core/Public/Logging/StructuredLog.h>
#include <ddsc/dds.h>

MORSE_API DECLARE_LOG_CATEGORY_EXTERN(LogMorse, Log, All)
MORSE_API DECLARE_LOG_CATEGORY_EXTERN(LogDDS, Log, All)

// Struct to map DDS return codes to their descriptions
struct FReturnCodeMapping
{
	int32 Code;
	const TCHAR* Description;
};

// Array of DDS return code mappings
static const FReturnCodeMapping ReturnCodeMappings[] =
{
	{ DDS_RETCODE_OK, TEXT("Success") },
	{ DDS_RETCODE_ERROR, TEXT("Non-specific error") },
	{ DDS_RETCODE_UNSUPPORTED, TEXT("Feature unsupported") },
	{ DDS_RETCODE_BAD_PARAMETER, TEXT("Bad parameter value") },
	{ DDS_RETCODE_PRECONDITION_NOT_MET, TEXT("Precondition not met") },
	{ DDS_RETCODE_OUT_OF_RESOURCES, TEXT("Out of resources") },
	{ DDS_RETCODE_NOT_ENABLED, TEXT("Feature not enabled") },
	{ DDS_RETCODE_IMMUTABLE_POLICY, TEXT("Immutable policy") },
	{ DDS_RETCODE_INCONSISTENT_POLICY, TEXT("Inconsistent policy") },
	{ DDS_RETCODE_ALREADY_DELETED, TEXT("Already deleted") },
	{ DDS_RETCODE_TIMEOUT, TEXT("Timeout occurred") },
	{ DDS_RETCODE_NO_DATA, TEXT("No data provided") },
	{ DDS_RETCODE_ILLEGAL_OPERATION, TEXT("Illegal operation") },
	{ DDS_RETCODE_NOT_ALLOWED_BY_SECURITY, TEXT("Not allowed by security") }
};

// Function to get the description of a return code 
static const TCHAR* GetReturnCodeDescription(int32 Code)
{
	for (const FReturnCodeMapping& Mapping : ReturnCodeMappings)
	{
		if (Mapping.Code == Code)
		{
			return Mapping.Description;
		}
	}
	return TEXT("Unknown error code");
}

#define RC_DDS_CHECK(rc) \
do { \
if ((rc) < 0) { \
UE_LOG(LogDDS, Log, TEXT("RC: %d - %s (File: %s, Function: %s, Line: %d)"), \
rc, GetReturnCodeDescription(rc), TEXT(__FILE__), TEXT(__FUNCTION__), __LINE__); \
} \
} while (0)