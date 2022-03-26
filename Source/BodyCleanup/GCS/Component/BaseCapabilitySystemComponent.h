// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CapabilitySystemComponent.h"
#include "BodyCleanup/ExDefines.h"
#include "BaseCapabilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UBaseCapabilitySystemComponent : public UCapabilitySystemComponent
{
	GENERATED_BODY()

public :
	virtual bool ApplyGameplayEffectToTargetWithAdvantage(TSoftObjectPtr<class UCAPEffect> CAPEffect, UCapabilitySystemComponent* Target, int32 AbilityLevel = 0, float Weight = 0);
	virtual void LeftAnimationType(EAnimationType AnimationType);
	virtual float GetAbilityRangeByTag(const FGameplayTag& Tag);
};
