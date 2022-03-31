// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetaTools/Variable/FloatVariableMetaData.h"
#include "CAPTypes.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECAPModifierOp : uint8
{
	Additive = 0,
	Multiply,
	Division,
	Override,
};

UENUM(BlueprintType)
enum class ECAPEffectMagnitudeType : uint8
{
	//기본 방식으로 입력한 Default 값에만 영향을 주게 됩니다.
	Default,
	//AbilityLevel에 따라 값을 다르게 설정할 수 있습니다.
	AbilityLevel,
};

UENUM(BlueprintType)
enum class ECAPEffectDurationPolicy : uint8
{
	//한 번만 실행합니다.
	Instant,
	//정해진 기간동안 실행합니다.
	Duration,
	//무한히 실행됩니다.
	Infinite UMETA(Hidden),
};

UENUM(BlueprintType)
enum class ECAPEffectStackingPolicy : uint8
{
	None,
	Count,
};

USTRUCT(BlueprintType)
struct FCAPEffectWeightMagnitude
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FFloatVariableMetaData BaseMagnitude;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FFloatVariableMetaData WeightMagnitude;

	float GetMagnitudeVariable(float Weight) const
	{
		float WeightMagnitudeValue = WeightMagnitude.GetMetaVariable().Get<float>();
		float WeightMagnitudeResult = WeightMagnitudeValue * Weight;
		float BaseMagnitudeResult =  BaseMagnitude.GetMetaVariable().Get<float>();

		return BaseMagnitudeResult + WeightMagnitudeResult;
	}
};

USTRUCT(BlueprintType)
struct FCAPEffectModifierEvaluatedData
{
	GENERATED_USTRUCT_BODY()

	//Attribute 이름 입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName						AttributeName;

	//어떻게 데미지를 줄 것인지에 대한 연산 방식을 선택합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECAPModifierOp				ModifierOp;

	//값을 전달할 방식에 대한 방법을 선택합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECAPEffectMagnitudeType		MagnitudeType;

	//기본 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCAPEffectWeightMagnitude	DefaultMagnitude;

	//Ability for Level
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MagnitudeType == ECAPEffectMagnitudeType::AbilityLevel", EditConditionHides))
	TArray<FCAPEffectWeightMagnitude>	AbilityLevelMagnitudes;

public :
	const FCAPEffectWeightMagnitude& GetWeightMagnitude(int32 AbilityLevel) const;
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

	//주기를 설정합니다. 만약 Duration이 2이고 Period가 0.5이면 총 4번 Effect가 실행됩니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					Period;

	//매 Period마다 영향을 줄 것인지를 설정합니다. 버프 같은 경우에는 false로 설정하여 1번만 실행하는 것이 좋습니다. 만약 true로 되면 중첩되어 버프효과가 배가 될 것입니다.
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

struct FOnCAPAttributeChangeData
{
	float OldValue;
	float NewValue;
	FName AttributeName;
	TSoftObjectPtr<class UCAPAttributeSet> AttributeSet;
	FHitResult HitResult;
};

USTRUCT(BlueprintType)
struct FCAPEffectAdvantage
{
	GENERATED_BODY()

	FCAPEffectAdvantage(){}
	FCAPEffectAdvantage(const FName& InPropertyName, float InAdvantage)
		: PropertyName(InPropertyName), Advantage(InAdvantage){}
	
	FName	PropertyName;
	float	Advantage;
};