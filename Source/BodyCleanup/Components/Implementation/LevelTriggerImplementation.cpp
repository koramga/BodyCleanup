// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTriggerImplementation.h"

bool CLevelTriggerImplementation::IsOnTrigger() const
{
	return false;
}

void CLevelTriggerImplementation::GetTriggerLocation(TArray<FVector>& TriggerLocations)
{
}

void CLevelTriggerImplementation::CallTriggerObservers(bool bInputIsTick)
{
}

void CLevelTriggerImplementation::AddTriggerObserver(TSoftObjectPtr<ILevelTriggerInterface> LevelTriggerInterface)
{
}

void CLevelTriggerImplementation::CalledTriggerObservers(TSoftObjectPtr<USceneComponent> CallerActorComponent, bool bInputIsTick)
{
}

CLevelTriggerImplementation::CLevelTriggerImplementation()
{
}

CLevelTriggerImplementation::~CLevelTriggerImplementation()
{
}
