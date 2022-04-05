// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVariableMetaData.h"
#include "UObject/Object.h"
#include "Vector4VariableMetaData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FNormalVector4MetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector4 Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FRangeVector4MetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector4	Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector4 Max;
};


USTRUCT(BlueprintType)
struct METATOOLS_API FVector4VariableMetaData : public FBaseVariableMetaData
{
	GENERATED_BODY()

public :
	FVector4VariableMetaData();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Normal", EditConditionHides))
	FNormalVector4MetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Range", EditConditionHides))
	FRangeVector4MetaData	RangeVariableMetaData;

public :
	virtual TMetaVariable GetMetaVariable() const override;
};
