// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleTriggerComponent.h"

UDestructibleTriggerComponent::UDestructibleTriggerComponent()
{

}

void UDestructibleTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDestructibleTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();
}

void UDestructibleTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);
}
