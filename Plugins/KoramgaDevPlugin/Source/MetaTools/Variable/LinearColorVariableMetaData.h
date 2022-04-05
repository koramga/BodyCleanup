// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVariableMetaData.h"
#include "UObject/Object.h"
#include "LinearColorVariableMetaData.generated.h"

/**
 * 
*/


USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FNormalLinearColorMetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FRangeLinearColorMetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor	Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor Max;
};


USTRUCT(BlueprintType)
struct METATOOLS_API FLinearColorVariableMetaData : public FBaseVariableMetaData
{
	GENERATED_BODY()

public :
	FLinearColorVariableMetaData();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Normal", EditConditionHides))
	FNormalLinearColorMetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Range", EditConditionHides))
	FRangeLinearColorMetaData	RangeVariableMetaData;

public :
	virtual TMetaVariable GetMetaVariable() const override;
};
