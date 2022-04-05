// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetaTools/Variable/FloatVariableMetaData.h"
#include "MetaTools/Variable/LinearColorVariableMetaData.h"
#include "MetaTools/Variable/VectorVariableMetaData.h"
#include "UObject/Object.h"
#include "MaterialInstanceVariable.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class EMaterialInstanceVariableType : uint8
{
	Float,
	Vector,
	LinearColor,
};

USTRUCT(BlueprintType)
struct METATOOLS_API FMaterialInstanceVariable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMaterialInstanceVariableType	MaterialInstanceVariable = EMaterialInstanceVariableType::Float;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MaterialInstanceVariable == EMaterialInstanceVariableType::Float", EditConditionHides))
	FFloatVariableMetaData			FloatVariableMetaData;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MaterialInstanceVariable == EMaterialInstanceVariableType::Vector", EditConditionHides))
	FVectorVariableMetaData			VectorVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MaterialInstanceVariable == EMaterialInstanceVariableType::LinearColor", EditConditionHides))
	FLinearColorVariableMetaData	LinearColorVariableMetaData;
	
};
