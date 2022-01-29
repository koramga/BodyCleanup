// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"

void USimpleGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(const_cast<AActor*>(TriggerEventData->Target));
	
	ApplyGameplayEffectToTarget(Handle, ActorInfo, ActivationInfo,  TriggerEventData->TargetData, ActivateGamePlayEffect, 1, 1);
}
