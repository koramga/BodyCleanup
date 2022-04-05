// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVariableMetaDataGroup.h"
#include "MetaTools/Variable/FloatVariableMetaData.h"
#include "MetaTools/Variable/LinearColorVariableMetaData.h"
#include "MetaTools/Variable/VectorVariableMetaData.h"
#include "UObject/Object.h"
#include "MaterialInstanceVariable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct METATOOLS_API FMaterialInstanceVariable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName						ParameterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32						DynamicMaterialInstanceElementIndex = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBaseVariableMetaDataGroup	BaseVariableMetaDataGroup;

protected:
	bool SetMaterialInstanceParameter(USkeletalMeshComponent* SkeletalMeshComponent);
	bool SetMaterialInstanceParameter(UMaterialInstanceDynamic* MaterialInstanceDynamic);
};
