// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyTriggerComponent.h"

UDestroyTriggerComponent::UDestroyTriggerComponent()
{
	bIsCanControlTriggerComponentFromType = false;
	TriggerComponentFromType = ETriggerComponentFromType::Action;
}

void UDestroyTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnDestroyed.AddDynamic(this, &UDestroyTriggerComponent::OnActorDestroyed);

	bIsTriggerDestroy = false;
}

void UDestroyTriggerComponent::OnActorDestroyed(AActor* DestroyedActor)
{
	if (false == bIsTriggerDestroy)
	{
		bIsTriggerDestroy = true;
		CallTriggerObservers(true);
	}
}