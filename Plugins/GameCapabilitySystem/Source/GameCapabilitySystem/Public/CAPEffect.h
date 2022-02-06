// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAPTypes.h"
#include "GameplayTagContainer.h"
#include "CAPEffect.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, Blueprintable)
class GAMECAPABILITYSYSTEM_API UCAPEffect : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effect")
	ECAPEffectDurationPolicy						DurationPolicy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effect", meta = (EditCondition = "DurationPolicy == ECAPEffectDurationPolicy::Duration", EditConditionHides))
	FCAPEffectDurationMagnitude						Duration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effect", meta = (EditCondition = "DurationPolicy != ECAPEffectDurationPolicy::Instant", EditConditionHides))
	FCAPEffectPeriodMagnitude						Period;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effect")
	TArray<FCAPEffectModifierEvaluatedData>			Modifiers;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stacking")
	FCAPEffectStack					Stack;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tags")
	FGameplayTagContainer			EffectAssetTags;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tags")
	FGameplayTagContainer			BlockAssetTags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tags")
	FGameplayTagContainer			RemovalAssetTags;

public :
	ECAPEffectDurationPolicy GetEffectDurationPolicy() const;
	const FCAPEffectDurationMagnitude* GetEffectDurationMagnitude() const;
	const FCAPEffectPeriodMagnitude* GetEffectPeriodMagnitude() const;
	const TArray<FCAPEffectModifierEvaluatedData>& GetModifierMagnitude() const;
	
};
