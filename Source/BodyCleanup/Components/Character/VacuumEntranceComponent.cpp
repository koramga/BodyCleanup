// Fill out your copyright notice in the Description page of Project Settings.


#include "VacuumEntranceComponent.h"

UVacuumEntranceComponent::UVacuumEntranceComponent()
{

}

void UVacuumEntranceComponent::SetHoldingActor(TSoftObjectPtr<AActor> InputHoldingActor)
{
	HoldingActor = InputHoldingActor;
}

TSoftObjectPtr<AActor> UVacuumEntranceComponent::GetHoldingActor() const
{
	return HoldingActor;
}

bool UVacuumEntranceComponent::HasHoldingActor() const
{
	return HoldingActor.IsValid();
}
