/*****************************************************************
* @file   MRSConvertUtils.h
 * @brief   This file contains different utility function used in Morse Plugin. (Conversion, Helper, etc)
 * 
 * @author Nicolas B.
 * @date   March 2024
 * @copyright Nicolas Brugie. All rights reserved.
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MRSConvertUtils.generated.h"

/**
 * 
 */
UCLASS()
class MORSE_API UMRSConvertUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public :
	/**
	 * @brief Converts an FString to char*.
	 * @details This operation converts an FString to a char*.
	 * @param inString The FString to convert.
	 * @param outString The resulting char*.
	 */
	static void UEStringToDDS(const FString inString, char*& outString) {
		const unsigned int msgStringCapacity = inString.Len() + 1;
		if (outString != nullptr)
		{
			free(outString);
		};
		outString = (char*)malloc(msgStringCapacity);
		memcpy(outString, TCHAR_TO_ANSI(*inString), msgStringCapacity);
	};

	/**
	 * @brief Converts a char* to FString.
	 * @details This operation converts a char* to FString.
	 * @param inString The char* to convert.
	 * @param outString The resulting FString.
	 */
	static void DDSStringToUE(const char* inString, FString& outString) {
		outString = FString(inString);
	};
};
