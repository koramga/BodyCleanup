// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveComponent.h"

// Sets default values for this component's properties
UInteractiveComponent::UInteractiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	//bIsCanControlTriggerComponentFromType = false;
	//TriggerComponentFromType = ETriggerComponentFromType::Action;

	// ...

	InteractiveType = EInteractiveType::None;
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

bool UInteractiveComponent::CanUpdateInteractive(EInteractiveAction NextInteractiveAction, EInteractiveAction CurrentInteractiveAction)
{
	return true;
}

EInteractiveAction UInteractiveComponent::GetInteractiveAction() const
{
	return InteractiveAction;
}

void UInteractiveComponent::SetInteractiveAction(EInteractiveAction InputInteractiveAction)
{
	if (InteractiveAction != InputInteractiveAction)
	{
		if (CanUpdateInteractive(InputInteractiveAction, InteractiveAction))
		{
			SetupInteractiveAction(InputInteractiveAction);
		}
	}
}

void UInteractiveComponent::SetInteractiveComponent(TSoftObjectPtr<USceneComponent> InputInteractiveComponent)
{
	InteractiveComponent = InputInteractiveComponent;
}

EInteractiveType UInteractiveComponent::GetInteractiveType() const
{
	return InteractiveType;
}

void UInteractiveComponent::SetInteractiveType(EInteractiveType InputInteractiveType)
{
	InteractiveType = InputInteractiveType;
}

void UInteractiveComponent::SetupInteractiveAction(EInteractiveAction InputInteractiveAction)
{
	UpdateInteractiveAction(InputInteractiveAction, InteractiveAction);
	//UpdateTriggerState(static_cast<uint8>(InputInteractiveAction));

	InteractiveAction = InputInteractiveAction;

	if (TriggerInteractiveActions.Find(InputInteractiveAction) >= 0)
	{
		//CallTriggerObservers(true);
	}
	else
	{
		//CallTriggerObservers(false);
	}
}
