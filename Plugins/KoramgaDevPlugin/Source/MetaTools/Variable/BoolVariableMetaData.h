// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVariableMetaData.h"
#include "UObject/Object.h"
#include "BoolVariableMetaData.generated.h"

/**
 * 
*/

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FNormalBooleanMetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FRangeBooleanMetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	Max;
};


USTRUCT(BlueprintType)
struct METATOOLS_API FBooleanVariableMetaData : public FBaseVariableMetaData
{
	GENERATED_BODY()

public :
	FBooleanVariableMetaData();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Normal", EditConditionHides))
	FNormalBooleanMetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Range", EditConditionHides))
	FRangeBooleanMetaData	RangeVariableMetaData;

public :
	virtual TMetaVariable GetMetaVariable() const override;
};
