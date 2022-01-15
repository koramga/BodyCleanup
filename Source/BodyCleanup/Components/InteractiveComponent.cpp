// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveComponent.h"

// Sets default values for this component's properties
UInteractiveComponent::UInteractiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bIsCanControlTriggerComponentFromType = false;
	TriggerComponentFromType = ETriggerComponentFromType::Action;

	// ...
}


// Called when the game starts
void UInteractiveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractiveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractiveComponent::UpdateInteractiveAction(EInteractiveAction NextInteractiveAction, EInteractiveAction BeforeInteractiveAction)
{
}

EInteractiveAction UInteractiveComponent::GetInteractiveAction() const
{
	return InteractiveAction;
}

void UInteractiveComponent::SetInteractiveAction(EInteractiveAction InputInteractiveAction)
{
	if (InteractiveAction != InputInteractiveAction)
	{
		UpdateInteractiveAction(InputInteractiveAction, InteractiveAction);

		InteractiveAction = InputInteractiveAction;

		if (TriggerInteractiveActions.Find(InputInteractiveAction) >= 0)
		{
			CallTriggerObservers(true);
			CallTriggerObservers(false);
		}
	}
}
