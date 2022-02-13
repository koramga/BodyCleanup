// Fill out your copyright notice in the Description page of Project Settings.


#include "VacuumEntranceComponent.h"
#include "BodyCleanup/Character/BaseCharacter.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "LevelDesignerTools/Utility/LevelSupportFunctionLibrary.h"
#include "Components/CapsuleComponent.h"

UVacuumEntranceComponent::UVacuumEntranceComponent()
{
}

void UVacuumEntranceComponent::__GrabActor()
{
	if (HoldingActor.IsValid())
	{
		UPrimitiveComponent* HoldingPrimitiveComponent = nullptr;
		UPrimitiveComponent* SizePrimitiveComponent = nullptr;

		if(HoldingActor->IsA(ABaseCharacter::StaticClass()))
		{
			const ABaseCharacter* HoldingCharacter = Cast<ABaseCharacter>(HoldingActor.Get());
			
			HoldingPrimitiveComponent = HoldingCharacter->GetMesh();
			SizePrimitiveComponent = HoldingCharacter->GetCapsuleComponent();
		}
		else
		{
			TArray<TSoftObjectPtr<UPrimitiveComponent>> PrimitiveComponents;

			ULevelSupportFunctionLibrary::FindPrimitiveComponets(PrimitiveComponents, HoldingActor.Get());

			for(const TSoftObjectPtr<UPrimitiveComponent>& PrimitiveComponent : PrimitiveComponents)
			{
				if(PrimitiveComponent->IsA(UStaticMeshComponent::StaticClass()))
				{
					HoldingPrimitiveComponent = PrimitiveComponent.Get();
					break;
				}
			}			
		}		

		if (IsValid(HoldingPrimitiveComponent)
			&& GrabConstraintComponent.IsValid()
			&& HeldObjectSlotComponent.IsValid())
		{
			float Size = 0;
		
			if (HoldingPrimitiveComponent->IsA(UStaticMeshComponent::StaticClass()))
			{
				UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(HoldingPrimitiveComponent);

				if (IsValid(StaticMeshComponent))
				{
					UStaticMesh* StaticMesh = StaticMeshComponent->GetStaticMesh();

					if (IsValid(StaticMesh))
					{
						FBoxSphereBounds StaticMeshBounds = StaticMesh->GetBounds();

						Size = StaticMeshBounds.GetBox().GetExtent().Size();
					}
				}
			}
			else if(HoldingPrimitiveComponent->IsA(USkeletalMeshComponent::StaticClass()))
			{
				USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(HoldingPrimitiveComponent);

				FVector ComponentOrigin;
				FVector ComponentBoxExtent;
				float	ComponentSphereRadius;

				if(IsValid(SizePrimitiveComponent))
				{
					UKismetSystemLibrary::GetComponentBounds(SizePrimitiveComponent, ComponentOrigin, ComponentBoxExtent, ComponentSphereRadius);					
				}
				else
				{
					UKismetSystemLibrary::GetComponentBounds(SkeletalMeshComponent, ComponentOrigin, ComponentBoxExtent, ComponentSphereRadius);					
				}				

				Size = ComponentBoxExtent.Size();
			}
			
			if(Size > 0.f)
			{
				HoldingPrimitiveComponent->SetWorldLocation(GetComponentToWorld().GetLocation() + GetOwner()->GetActorForwardVector() * Size / 2.f, false, nullptr, ETeleportType::ResetPhysics);	
			}			
			
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

bool UVacuumEntranceComponent::IsSucking() const
{
	return bIsSucking;
}

void UVacuumEntranceComponent::SetSucking(bool bInputIsSucking)
{
	bIsSucking = bInputIsSucking;
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

		if(IsSucking())
		{
			SetSucking(false);
		}
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

void UVacuumEntranceComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UVacuumEntranceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
