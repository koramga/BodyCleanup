// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveTriggerComponent.h"

UInteractiveTriggerComponent::UInteractiveTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractiveTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);
}

void UInteractiveTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractiveTriggerComponent::SetInteractiveType(uint8 InputInteractiveType)
{
	InteractiveType = InputInteractiveType;
	
	UpdateTriggerState(InteractiveType);
}

bool UInteractiveTriggerComponent::CanUpdateInteractiveType(uint8 CurrentInteractiveType, uint8 DesiredInteractiveType)
{
	return true;
}

void UInteractiveTriggerComponent::UpdateInteractiveType(uint8 CurrentInteractiveType, uint8 BeforeInteractiveType)
{
}

bool UInteractiveTriggerComponent::UpdateInteractiveType(uint8 InputInteractiveType)
{
	if(false == CanUpdateInteractiveType(InputInteractiveType))
	{
		return false;
	}

	UpdateInteractiveType(InputInteractiveType, InteractiveType);
	SetInteractiveType(InputInteractiveType);
	
	return true;
}

uint8 UInteractiveTriggerComponent::GetInteractiveType() const
{
	return InteractiveType;
}

bool UInteractiveTriggerComponent::CanUpdateInteractiveType(uint8 InputInteractiveType)
{
	if(CanUpdateInteractiveType(InteractiveType, InputInteractiveType))
	{
		return true;
	}

	return false;
}
