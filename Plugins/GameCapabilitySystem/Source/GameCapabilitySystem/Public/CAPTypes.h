// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetaTools/Variable/FloatVariableMetaData.h"
#include "CAPTypes.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class CAPModifierOp : uint8
{
	Additive = 0,
	Multiply,
	Division,
	Override,
};

UENUM(BlueprintType)
enum class ECAPEffectMagnitudeType : uint8
{
	AbilityLevel,
	Direct,
};

UENUM(BlueprintType)
enum class ECAPEffectDurationPolicy : uint8
{
	Instant,
	Infinite,
	Duration,	
};

UENUM(BlueprintType)
enum class ECAPEffectStackingPolicy : uint8
{
	None,
	Count,
};

USTRUCT(BlueprintType)
struct FCAPEffectModifierMagnitude
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32					AbilityLevel;					
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FFloatVariableMetaData	Magnitude;
};

USTRUCT(BlueprintType)
struct FCAPEffectModifierEvaluatedData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName					AttributeName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	CAPModifierOp			ModifierOp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECAPEffectMagnitudeType	MagnitudeType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MagnitudeType == ECAPEffectMagnitudeType::Direct", EditConditionHides))
	FFloatVariableMetaData	Magnitude;
};

USTRUCT(BlueprintType)
struct FCAPEffectDurationMagnitude
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					Duration;
};

USTRUCT(BlueprintType)
struct FCAPEffectPeriodMagnitude
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					Period;

	//매 Period마다 영향을 줄 것이냐 (버프같은경우에는 Duration은 존재하지만 한 번만 실행시킬 수 있어야 한다.)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool					ExecutePeriodicEffectOnApplication = true; 
};

USTRUCT(BlueprintType)
struct FCAPEffectStack
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECAPEffectStackingPolicy	Policy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "Policy == ECAPEffectStackingPolicy::Count", EditConditionHides))
	int32						Count;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "Policy == ECAPEffectStackingPolicy::Count", EditConditionHides))
	bool						bIsRefreshDuration;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "Policy == ECAPEffectStackingPolicy::Count", EditConditionHides))
	bool						bIsRefreshPeriod;
};
