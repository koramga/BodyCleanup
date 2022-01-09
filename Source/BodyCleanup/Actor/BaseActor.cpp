// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActor.h"
#include "../Components/InteractiveMovementComponent.h"

// Sets default values
ABaseActor::ABaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseActor::BeginPlay()
{
	Super::BeginPlay();
	
	InteractiveMovementComponent = Cast<UInteractiveMovementComponent>(GetComponentByClass(UInteractiveMovementComponent::StaticClass()));
}

// Called every frame
void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseActor::__SetEnabledCollisions(USceneComponent* SceneComponent, ECollisionEnabled::Type CollisionEnabledType)
{
	UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(SceneComponent);

	if (IsValid(PrimitiveComponent))
	{
		PrimitiveComponent->SetCollisionEnabled(CollisionEnabledType);
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		__SetEnabledCollisions(ChildComponent, CollisionEnabledType);
	}
}

void ABaseActor::__SetEnabledSimulations(USceneComponent* SceneComponent, bool bIsEnableSimulation)
{
	UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(SceneComponent);

	if (IsValid(PrimitiveComponent))
	{
		PrimitiveComponent->SetSimulatePhysics(bIsEnableSimulation);
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		__SetEnabledSimulations(ChildComponent, bIsEnableSimulation);
	}
}

void ABaseActor::__SetCollisionProfileNames(USceneComponent* SceneComponent, const FName& ProfileName)
{
	UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(SceneComponent);

	if (IsValid(PrimitiveComponent))
	{
		PrimitiveComponent->SetCollisionProfileName(ProfileName);
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		__SetCollisionProfileNames(ChildComponent, ProfileName);
	}
}

bool ABaseActor::IsInteractiveActor() const
{
	if (IsValid(InteractiveMovementComponent))
	{
		return true;
	}

	return false;
}

void ABaseActor::SetInteractiveActivate(bool bActivate)
{
	if (bActivate)
	{
		InteractiveMovementComponent->Activate();
	}
	else
	{
		InteractiveMovementComponent->Deactivate();
	}
}

UInteractiveMovementComponent* ABaseActor::GetInteractiveMovementComponent() const
{
	return InteractiveMovementComponent;
}

void ABaseActor::SetEnabledCollisions(bool bIsEnableCollision)
{
	ECollisionEnabled::Type CollisionEnabledType;

	if (bIsEnableCollision)
	{
		CollisionEnabledType = ECollisionEnabled::Type::QueryAndPhysics;
	}
	else
	{
		CollisionEnabledType = ECollisionEnabled::Type::NoCollision;
	}

	__SetEnabledCollisions(GetRootComponent(), CollisionEnabledType);
}

void ABaseActor::SetEnableSimulations(bool bIsEnableSimulation)
{
	__SetEnabledSimulations(GetRootComponent(), bIsEnableSimulation);
}

void ABaseActor::SetCollisionProfileNames(const FName& ProfileName)
{
	__SetCollisionProfileNames(GetRootComponent(), ProfileName);
}
