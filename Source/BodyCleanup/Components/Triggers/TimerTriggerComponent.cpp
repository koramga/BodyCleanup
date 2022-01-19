// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerTriggerComponent.h"

UTimerTriggerComponent::UTimerTriggerComponent()
{
	bIsCanControlTriggerComponentFromType = false;
	//TriggerComponentFromType = ETriggerComponentFromType::Action;
}

void UTimerTriggerComponent::BeginPlay()
{
	Super::BeginPlay(); 
	

	GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UTimerTriggerComponent::__AdvanceTimer, CycleTime, true);
}

void UTimerTriggerComponent::__AdvanceTimer()
{
	CallTriggerObservers(true);

	if (false == bIsLoopCycle)
	{		
		GetOwner()->GetWorldTimerManager().ClearTimer(TimerHandle);
	}
	else
	{
		CallTriggerObservers(false);
	}
}