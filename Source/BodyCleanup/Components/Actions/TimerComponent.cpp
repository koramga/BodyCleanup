// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerComponent.h"

void UTimerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTimerComponent::OnTrigger(bool bInputIsOnTrigger)
{
	if (true == bInputIsOnTrigger)
	{
		GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UTimerComponent::__AdvanceTimer, CycleTime, true);
	}
	else
	{
		GetOwner()->GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void UTimerComponent::__AdvanceTimer()
{
	CallTriggerObserversOnce();
}