// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVariableMetaData.h"
#include "FloatVariableMetaData.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FNormalFloatMetaData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FRangeFloatMetaData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	Max;
};


USTRUCT(BlueprintType)
struct METATOOLS_API FFloatVariableMetaData : public FBaseVariableMetaData
{
	GENERATED_BODY()

public :
	FFloatVariableMetaData();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Normal", EditConditionHides))
	FNormalFloatMetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Range", EditConditionHides))
	FRangeFloatMetaData		RangeVariableMetaData;

public:
	virtual TMetaVariable GetMetaVariable() const override;
	
};
