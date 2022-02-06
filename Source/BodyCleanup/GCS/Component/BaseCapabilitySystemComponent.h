// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CapabilitySystemComponent.h"
#include "BaseCapabilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UBaseCapabilitySystemComponent : public UCapabilitySystemComponent
{
	GENERATED_BODY()

public :
	virtual bool ApplyGameplayEffectToTargetWithAdvantage(class UCAPEffect* CAPEffect, UCapabilitySystemComponent* Target, int32 AbilityLevel = 0);
	
};
