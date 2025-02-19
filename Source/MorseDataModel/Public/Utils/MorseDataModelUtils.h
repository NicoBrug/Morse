// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Utils/MRSConvertUtils.h"
#include "CycloneImpl/Math/Geometry.h"
#include "MorseDataModelUtils.generated.h"

/**
 * 
 */
UCLASS()
class MORSEDATAMODEL_API UMorseDataModelUtils : public UMRSConvertUtils
{
	GENERATED_BODY()

public:
	static void UEVectorToDDS(const FVector& InVector, Unreal_Math_Vector3& OutVector)
	{
		OutVector.X = InVector.X;
		OutVector.Y = InVector.Y;
		OutVector.Z = InVector.Z;
	};

	static void DDSVectorToUE(const Unreal_Math_Vector3& InVector, FVector& OutVector)
	{
		OutVector.X = InVector.X;
		OutVector.Y = InVector.Y;
		OutVector.Z = InVector.Z;
	};

	static void UEQuaternionToDDS(FQuat InQuat, Unreal_Math_Quaternion& OutQuat)
	{
		OutQuat.X = InQuat.X;
		OutQuat.Y = InQuat.Y;
		OutQuat.Z = InQuat.Z;
		OutQuat.W = InQuat.W;
	};
	
	static void DDSQuaternionToUE(const Unreal_Math_Quaternion& InQuat, FQuat& OutQuat)
	{
		OutQuat.X = InQuat.X;
		OutQuat.Y = InQuat.Y;
		OutQuat.Z = InQuat.Z;
		OutQuat.W = InQuat.W;
	};

	static void UETransformToDDS(const FTransform InTransform, Unreal_Math_Transform& OutTransform)
	{
		UEQuaternionToDDS(InTransform.GetRotation(), OutTransform.Rotation);
		UEVectorToDDS(InTransform.GetTranslation(), OutTransform.Translation);
		UEVectorToDDS(InTransform.GetScale3D(), OutTransform.Scale3D);
	};
	
	static void DDSTransformToUE(const Unreal_Math_Transform& InTransform, FTransform& OutTransform)
	{
		FQuat NewQuaternion;
		FVector NewTranslation;
		FVector NewScale;
		
		DDSQuaternionToUE(InTransform.Rotation,NewQuaternion);
		OutTransform.SetRotation(NewQuaternion);

		DDSVectorToUE(InTransform.Translation,NewTranslation);
		OutTransform.SetTranslation(NewTranslation);

		DDSVectorToUE(InTransform.Scale3D,NewScale);
		OutTransform.SetScale3D(NewScale);
	};
};
