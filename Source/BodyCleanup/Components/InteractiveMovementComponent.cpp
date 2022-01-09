// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveMovementComponent.h"
#include "../Actor/BaseActor.h"
#include "../Character/BaseCharacter.h"

UInteractiveMovementComponent::UInteractiveMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	AbsorbingInterpValue = 0.05f;
}

void UInteractiveMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(true);
}

void UInteractiveMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (EInteractiveAction::Absorbing == InteractiveAction)
	{
		AActor* Owner = GetOwner();

		FVector NextLocation = FMath::VInterpTo(Owner->GetActorLocation(), InteractiveTransform.GetLocation(), DeltaTime, AbsorbingInterpValue);

		Owner->SetActorLocation(NextLocation);
	}
	else if (EInteractiveAction::Holding == InteractiveAction)
	{
		AActor* Owner = GetOwner();

		Owner->SetActorTransform(InteractiveTransform);
	}

	SetComponentTickEnabled(true);
}

EInteractiveAction UInteractiveMovementComponent::GetInteractiveAction() const
{
	return InteractiveAction;
}

EInteractiveType UInteractiveMovementComponent::GetInteractiveType() const
{
	return InteractiveType;
}

void UInteractiveMovementComponent::SetInteractiveAction(EInteractiveAction InputInteractiveAction)
{
	InteractiveAction = InputInteractiveAction;

	if (EInteractiveAction::None == InteractiveAction)
	{
		AActor* Owner = GetOwner();

		if (Owner->IsA(ABaseActor::StaticClass()))
		{
	//		Cast<ABaseActor>(Owner)->SetEnabledCollisions(true);
			Cast<ABaseActor>(Owner)->SetEnableSimulations(true);
			Cast<ABaseActor>(Owner)->SetCollisionProfileNames(TEXT("BlockAllDynamic"));
		}
	}
	else
	{
		AActor* Owner = GetOwner();

		if (Owner->IsA(ABaseActor::StaticClass()))
		{
	//		Cast<ABaseActor>(Owner)->SetEnabledCollisions(false);
			Cast<ABaseActor>(Owner)->SetEnableSimulations(false);
			Cast<ABaseActor>(Owner)->SetCollisionProfileNames(TEXT("OverlapAll"));
		}
	}
}

void UInteractiveMovementComponent::SetInteractiveTransform(const FTransform& Transform)
{
	InteractiveTransform = Transform;
}