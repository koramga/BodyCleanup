// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "SimpleGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API USimpleGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|BaseGamePlayAbility")
	TSubclassOf<class UGameplayEffect>	ActivateGamePlayEffect;

protected :
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
