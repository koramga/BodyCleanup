// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerActorComponent.h"

// Sets default values for this component's properties
UTriggerActorComponent::UTriggerActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTriggerActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTriggerActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTriggerActorComponent::GetTriggerLocation(TArray<FVector>& TriggerLocations)
{
}

void UTriggerActorComponent::UpdateTrigger(bool bInputIsOnTrigger)
{
}

const FLevelTriggerInput* UTriggerActorComponent::GetLevelTriggerInput() const
{
	return &LevelTriggerInput;
}

