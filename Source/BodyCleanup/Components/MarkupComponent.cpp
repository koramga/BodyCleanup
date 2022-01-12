﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkupComponent.h"

// Sets default values for this component's properties
UMarkupComponent::UMarkupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SetMobility(EComponentMobility::Static);

	// ...
}


// Called when the game starts
void UMarkupComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMarkupComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EMarkupType UMarkupComponent::GetMarkupType() const
{
	return MarkupType;
}

