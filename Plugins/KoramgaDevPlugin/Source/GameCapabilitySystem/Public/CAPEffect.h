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
	//데미지를 주는 방식에 대한 정책을 설정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effect")
	ECAPEffectDurationPolicy						DurationPolicy;

	//지속시간에 대한 값을 설정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effect", meta = (EditCondition = "DurationPolicy == ECAPEffectDurationPolicy::Duration", EditConditionHides))
	FCAPEffectDurationMagnitude						Duration;

	//주기에 대한 값을 설정합니다. 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effect", meta = (EditCondition = "DurationPolicy != ECAPEffectDurationPolicy::Instant", EditConditionHides))
	FCAPEffectPeriodMagnitude						Period;

	//변경사항에 대한 값 설정입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effect")
	TArray<FCAPEffectModifierEvaluatedData>			Modifiers;

protected:
	//얼마나 중첩되어 들어갈지를 결정합니다. (아직 미구현 상태입니다.)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stacking")
	FCAPEffectStack					Stack;

protected:
	//효과를 줄 경우에 들어가는 Tag입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tags")
	FGameplayTagContainer			EffectAssetTags;

	//해당 효과가 지속되는 동안 BlockAssetTag효과는 들어올 수 없습니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tags")
	FGameplayTagContainer			BlockAssetTags;

	//효과가 들어갈 경우 RemovalAssetTags의 Query Effect는 제거됩니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tags")
	FGameplayTagContainer			RemovalAssetTags;

public :
	ECAPEffectDurationPolicy GetEffectDurationPolicy() const;
	const FCAPEffectDurationMagnitude* GetEffectDurationMagnitude() const;
	const FCAPEffectPeriodMagnitude* GetEffectPeriodMagnitude() const;
	const TArray<FCAPEffectModifierEvaluatedData>& GetModifierMagnitude() const;
	const FGameplayTagContainer& GetEffectAssetTags() const;
	const FGameplayTagContainer& GetBlockAssetTags() const;
	const FGameplayTagContainer& GetRemovalAssetTags() const;
	
};
