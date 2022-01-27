// Fill out your copyright notice in the Description page of Project Settings.


#include "GameActorSettingsComponent.h"

// Sets default values for this component's properties
UGameActorSettingsComponent::UGameActorSettingsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	WeightType = EWeightType::None;
}


// Called when the game starts
void UGameActorSettingsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGameActorSettingsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EWeightType UGameActorSettingsComponent::GetWeightType() const
{
	return WeightType;
}

void UGameActorSettingsComponent::SetWeightType(EWeightType InputWeightType)
{
	WeightType = InputWeightType;
}

