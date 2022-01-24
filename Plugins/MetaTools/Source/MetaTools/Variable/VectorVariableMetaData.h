// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVariableMetaData.h"
#include "VectorVariableMetaData.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FNormalVectorMetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Vector;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FRangeVectorMetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector	Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Max;
};


USTRUCT(BlueprintType)
struct METATOOLS_API FVectorVariableMetaData : public FBaseVariableMetaData
{
	GENERATED_BODY()

public :
	FVectorVariableMetaData();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Normal", EditConditionHides))
	FNormalVectorMetaData	NormalVectorMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Range", EditConditionHides))
	FRangeVectorMetaData	RangeVectorMetaData;

public :
	virtual TMetaVariable GetMetaVariable() const override;
};
