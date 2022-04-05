// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVariableMetaData.h"
#include "UObject/Object.h"
#include "IntegerVariableMetaData.generated.h"

/**
 * 
*/

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FNormalIntegerMetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FRangeIntegerMetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int	Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Max;
};


USTRUCT(BlueprintType)
struct METATOOLS_API FIntegerVariableMetaData : public FBaseVariableMetaData
{
	GENERATED_BODY()

public :
	FIntegerVariableMetaData();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Normal", EditConditionHides))
	FNormalIntegerMetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Range", EditConditionHides))
	FRangeIntegerMetaData	RangeVariableMetaData;

public :
	virtual TMetaVariable GetMetaVariable() const override;
};
