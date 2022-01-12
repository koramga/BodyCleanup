// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"

UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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
	bIsUpdateAfterTransformed = bInputIsOnTrigger;
}

void UActionComponent::UpdateTrigger(bool bInputIsOnTrigger)
{
	Super::UpdateTrigger(bInputIsOnTrigger);

	if (EActionComponentActionType::On == ActionType)
	{
		if (false == bIsUpdateAfterTransformed)
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
