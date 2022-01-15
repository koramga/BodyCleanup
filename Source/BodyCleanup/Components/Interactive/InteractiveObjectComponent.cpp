// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObjectComponent.h"

UInteractiveObjectComponent::UInteractiveObjectComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractiveObjectComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractiveObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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

		Owner->SetActorLocation(InteractiveTransform.GetLocation());
		Owner->SetActorRotation(InteractiveTransform.GetRotation());
	}

}

void UInteractiveObjectComponent::UpdateInteractiveAction(EInteractiveAction NextInteractiveAction, EInteractiveAction BeforeInteractiveAction)
{
	Super::UpdateInteractiveAction(NextInteractiveAction, BeforeInteractiveAction);

	//if (EInteractiveAction::None == InteractiveAction
	//	|| EInteractiveAction::Shooting == InteractiveAction)
	//{
	//	AActor* Owner = GetOwner();
	//
	//	if (Owner->IsA(AActor::StaticClass()))
	//	{
	//		Cast<ABaseActor>(Owner)->SetEnableSimulations(true);
	//	}
	//}
	//else
	//{
	//	AActor* Owner = GetOwner();
	//
	//	if (Owner->IsA(ABaseActor::StaticClass()))
	//	{
	//		Cast<ABaseActor>(Owner)->SetEnableSimulations(false);
	//	}
	//
	//}

}

EInteractiveObjectType UInteractiveObjectComponent::GetInteractiveObjectType() const
{
	return InteractiveObjectType;
}
