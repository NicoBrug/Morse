/*****************************************************************
* @file   MRSConvertUtils.h
 * @brief   This file contains different utility functions used in the Morse Plugin. (Conversion, Helper, etc)
 * 
 * @author Nicolas B.
 * @date   March 2024
 * @copyright Nicolas Brugie. All rights reserved.
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

/**
 * @class UMRSConvertUtils
 * @brief Utility class for conversion functions used in the Morse Plugin.
 * 
 * This class provides static methods to convert between Unreal Engine types (e.g., FString) and other data types (e.g., char*).
 */
class MORSE_API MRSConvertUtils
{
public:
	/**
	 * @brief Converts an FString to a char*.
	 * @details This function converts an FString to a dynamically allocated char*. The caller is responsible for freeing the memory.
	 * @param inString The FString to convert.
	 * @param outString The resulting char*. This pointer will be allocated by the function.
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
	 * @brief Converts a char* to an FString.
	 * @details This function converts a char* to an FString. It handles null input by returning an empty string.
	 * @param inString The char* to convert.
	 * @param outString The resulting FString.
	 */
	static void DDSStringToUE(const char* inString, FString& outString) {
		if (inString) {
			outString = FString(StringCast<TCHAR>(inString));
		} else {
			outString.Empty();
		}
	};

	/**
	 * @brief Converts a sequence of elements to a TArray.
	 * @details This template function converts a sequence of elements (e.g., a sequence representation in IDL) to a TArray. It supports both arithmetic and custom types.
	 * @tparam TSequence The type of the input sequence.
	 * @tparam T The type of the elements in the TArray.
	 * @param InSequence The input sequence to convert.
	 * @param OutArray The resulting TArray.
	 * @param Size The size of the input sequence.
	 */
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

	/**
	 * @brief Converts a TArray to a sequence of elements.
	 * @details This template function converts a TArray to a sequence of elements (e.g., a sequence representation in IDL). It supports both arithmetic and custom types.
	 * @tparam TSequence The type of the output sequence.
	 * @tparam T The type of the elements in the TArray.
	 * @param InArray The input TArray to convert.
	 * @param OutSequence The resulting sequence.
	 * @param Size The size of the output sequence.
	 */
	template<typename TSequence, typename T>
	static void TArrayToSequence(TArray<T>& InArray, TSequence* OutSequence, const int Size)
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

	/**
	 * @brief Converts a sequence of strings to a TArray of FStrings.
	 * @details This template function converts a sequence of strings (e.g., char*) to a TArray of FStrings.
	 * @tparam TSequence The type of the input sequence (e.g., char**).
	 * @tparam T The type of the elements in the TArray (e.g., FString).
	 * @param InSequence The input sequence of strings to convert.
	 * @param OutArray The resulting TArray of FStrings.
	 * @param Size The size of the input sequence.
	 */
	template<typename TSequence, typename T>
	static void StrSequenceToTArray(const TSequence* InSequence, TArray<T>& OutArray, const int Size)
	{
		OutArray.Empty();
		for (int i = 0; i < Size  ; ++i) {
			FString OutString;
			const char* InString = InSequence[i];
			DDSStringToUE(InString, OutString);
			OutArray.Add(OutString);
		};
	}

	/**
	 * @brief Converts a TArray of FStrings to a sequence of strings.
	 * @details This template function converts a TArray of FStrings to a sequence of strings (e.g., char*).
	 * @tparam TSequence The type of the output sequence (e.g., char**).
	 * @tparam T The type of the elements in the TArray (e.g., FString).
	 * @param InArray The input TArray of FStrings to convert.
	 * @param OutSequence The resulting sequence of strings.
	 * @param Size The size of the output sequence.
	 */
	template<typename TSequence, typename T>
	static void StrTArrayToSequence(TArray<T>& InArray, TSequence* OutSequence, const int Size)
	{
		for (int i = 0; i < Size; ++i) {
			UEStringToDDS(InArray[i], OutSequence[i]);
		}
	}
};