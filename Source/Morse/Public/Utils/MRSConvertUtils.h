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
		if (inString) {
			outString = FString(StringCast<TCHAR>(inString));
		} else {
			outString.Empty(); // Handle null input gracefully
		}
	};

	

	template<typename TSequence, typename T>
	static void SequenceToTArray(const TSequence* InSequence, TArray<T>& OutArray, const int Size)
	{
		OutArray.SetNum(Size);
		for (auto i = 0; i < Size; ++i)
		{
			if constexpr (TIsArithmetic<T>::Value)
			{
				OutArray[i] = InSequence[i];
			}
			else
			{
				OutArray[i].DDSToUE(InSequence[i]);
			}
		}
	}


	template<typename TSequence, typename T>
	static void TArrayToSequence(TArray<T>& InArray, TSequence* OutSequence, const int Size) //need const ?? const TArray<T>& InArray
	{
		for (auto i = 0; i < Size; ++i)
		{
			if constexpr (TIsArithmetic<T>::Value)
			{
				OutSequence[i] = InArray[i];
			}
			else
			{
				InArray[i].UEToDDS(OutSequence[i]);
			}
		}
	}


	template<typename TSequence, typename T>
	static void StrSequenceToTArray(const TSequence* InSequence, TArray<T>& OutArray, const int Size) //need const ?? const TArray<T>& InArray
	{
		OutArray.Empty();
		for (int i = 0; i < Size  ; ++i) {
			FString OutString;
			const char* InString = InSequence[i];
			DDSStringToUE(InString, OutString);
			OutArray.Add(OutString);
		};
	}

	template<typename TSequence, typename T>
	static void StrTArrayToSequence(TArray<T>& InArray, TSequence* OutSequence, const int Size) //need const ?? const TArray<T>& InArray
	{
		for (int i = 0; i < Size; ++i) {
			UEStringToDDS(InArray[i], OutSequence[i]);
		}
	}
};
