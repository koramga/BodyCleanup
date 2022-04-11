// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeDilationTriggerComponent.h"

UTimeDilationTriggerComponent::UTimeDilationTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTimeDilationTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false);
}

void UTimeDilationTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();
}

void UTimeDilationTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	if(InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		SetComponentTickEnabled(true);
		TickTime = 0.f;
		//GetWorld()->GetWorldSettings()->SetTimeDilation()
	}
}

void UTimeDilationTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TickTime += DeltaTime / GetWorld()->GetWorldSettings()->TimeDilation;

	if(TickTime > KeepTime)
	{
		GetWorld()->GetWorldSettings()->SetTimeDilation(1.f);
		SetComponentTickEnabled(false);
	}
	else
	{
		if(GetWorld()->GetWorldSettings()->TimeDilation != TimeDilation)
		{
			GetWorld()->GetWorldSettings()->SetTimeDilation(TimeDilation);
		}
	}
}
