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
	ECAPEffectDurationPolicy				DurationPolicy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effect", meta = (EditCondition = "DurationPolicy == ECAPEffectDurationPolicy::Duration", EditConditionHides))
	FCAPEffectModifierMagnitude				Duration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effect", meta = (EditCondition = "DurationPolicy != ECAPEffectDurationPolicy::Instant", EditConditionHides))
	FCAPEffectPeriodMagnitude				Period;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effect")
	FCAPEffectModifierEvaluatedData			Modifiers;

protected:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Magnitude")
	TArray<FCAPEffectModifierMagnitude>		Magnitudes;

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
};
