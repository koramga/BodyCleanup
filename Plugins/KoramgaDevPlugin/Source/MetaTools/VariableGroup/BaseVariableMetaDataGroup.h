// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetaTools/Variable/BaseVariableMetaData.h"
#include "MetaTools/Variable/BoolVariableMetaData.h"
#include "MetaTools/Variable/FloatVariableMetaData.h"
#include "MetaTools/Variable/IntegerVariableMetaData.h"
#include "MetaTools/Variable/LinearColorVariableMetaData.h"
#include "MetaTools/Variable/Vector4VariableMetaData.h"
#include "MetaTools/Variable/VectorVariableMetaData.h"
#include "UObject/Object.h"
#include "BaseVariableMetaDataGroup.generated.h"

/**
 * 
*/

USTRUCT(BlueprintType)
struct METATOOLS_API FBaseVariableMetaDataGroup
{
	GENERATED_BODY()

public :
	FBaseVariableMetaDataGroup();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMetaVariableType	MetaVariableType = EMetaVariableType::Float;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableType == EMetaVariableType::Bool", EditConditionHides))
	FBooleanVariableMetaData		BoolVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableType == EMetaVariableType::Int", EditConditionHides))
	FIntegerVariableMetaData		IntVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableType == EMetaVariableType::Float", EditConditionHides))
	FFloatVariableMetaData			FloatVariableMetaData;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableType == EMetaVariableType::Vector", EditConditionHides))
	FVectorVariableMetaData			VectorVariableMetaData;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableType == EMetaVariableType::Vector4", EditConditionHides))
	FVector4VariableMetaData		Vector4VariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableType == EMetaVariableType::LinearColor", EditConditionHides))
	FLinearColorVariableMetaData	LinearColorVariableMetaData;

public :
	virtual TMetaVariable GetMetaVariable() const;
	EMetaVariableType GetMetaVariableType() const;
};
