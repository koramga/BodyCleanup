// Fill out your copyright notice in the Description page of Project Settings.


#include "VacuumEntranceComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

UVacuumEntranceComponent::UVacuumEntranceComponent()
{

}

void UVacuumEntranceComponent::__GrabActor()
{
	if (HoldingActor.IsValid())
	{
		UPrimitiveComponent* HoldingPrimitiveComponent = Cast<UPrimitiveComponent>(HoldingActor->GetComponentByClass(UPrimitiveComponent::StaticClass()));

		if (IsValid(HoldingPrimitiveComponent)
			&& GrabConstraintComponent.IsValid()
			&& HeldObjectSlotComponent.IsValid())
		{
			//HeldObjectSlotComponent->SetWorldLocation(HoldingActor.Get()->GetActorLocation(), false, nullptr, ETeleportType::ResetPhysics);
			GrabConstraintComponent->SetConstrainedComponents(HeldObjectSlotComponent.Get(), NAME_None, HoldingPrimitiveComponent, NAME_None);
		}
	}
}

void UVacuumEntranceComponent::__DropActor()
{
	if (HoldingActor.IsValid())
	{
		if (GrabConstraintComponent.IsValid())
		{
			GrabConstraintComponent->BreakConstraint();
		}
	}
}

void UVacuumEntranceComponent::SetHoldingActor(TSoftObjectPtr<AActor> InputHoldingActor)
{
	if (HoldingActor.IsValid())
	{
		__DropActor();
	}

	HoldingActor = InputHoldingActor;

	if (HoldingActor.IsValid())
	{
		__GrabActor();
	}
}

TSoftObjectPtr<AActor> UVacuumEntranceComponent::GetHoldingActor() const
{
	return HoldingActor;
}

bool UVacuumEntranceComponent::HasHoldingActor() const
{
	return HoldingActor.IsValid();
}

void UVacuumEntranceComponent::SetHeldObjectSlot(UStaticMeshComponent* InputHeldObjectSlotComponent)
{
	HeldObjectSlotComponent = InputHeldObjectSlotComponent;
}

void UVacuumEntranceComponent::SetGrabConstraintComponent(UPhysicsConstraintComponent* InputGrabConstraintComponent)
{
	GrabConstraintComponent = InputGrabConstraintComponent;
}
