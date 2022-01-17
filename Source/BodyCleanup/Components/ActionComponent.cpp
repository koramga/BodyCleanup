// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"
#include "Interfaces/LevelMarkupInterface.h"

UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UActionComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActionComponent::OnTrigger(bool bInputIsOnTrigger)
{
	bIsUpdateDestinationTransformed = bInputIsOnTrigger;
}

void UActionComponent::UpdateTrigger(bool bInputIsOnTrigger)
{
	Super::UpdateTrigger(bInputIsOnTrigger);

	if (EActionComponentActionType::On == ActionType)
	{
		if (false == bIsUpdateDestinationTransformed)
		{
			if (true == bInputIsOnTrigger)
			{
				OnTrigger(bInputIsOnTrigger);
			}
		}
	}
	else
	{
		OnTrigger(bIsOnTrigger);
	}	
}

bool UActionComponent::IsUpdateDestinationTransformed() const
{
	return bIsUpdateDestinationTransformed;
}
