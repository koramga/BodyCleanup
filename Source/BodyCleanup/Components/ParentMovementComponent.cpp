// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentMovementComponent.h"

// Sets default values for this component's properties
UParentMovementComponent::UParentMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UParentMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//DestinationTransform =  GetTransform()

	USceneComponent* AttachParentComponent = GetAttachParent();

	if (IsValid(AttachParentComponent))
	{
		AttachParentComponent->Mobility = EComponentMobility::Type::Movable;

		DestinationTransform = AttachParentComponent->GetRelativeTransform() + GetRelativeTransform();
		DestinationTransform.SetRotation((AttachParentComponent->GetRelativeRotation() + GetRelativeRotation()).Quaternion());
	}
	
}


// Called every frame
void UParentMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...


	USceneComponent* AttachParentComponent = GetAttachParent();

	if (IsValid(AttachParentComponent))
	{
		FTransform Source = AttachParentComponent->GetRelativeTransform();

		if (bIsUpdateScale)
		{
			AttachParentComponent->SetRelativeScale3D(FMath::VInterpTo(Source.GetScale3D(), DestinationTransform.GetScale3D(), DeltaTime, InterpSpeed));
		}

		if (bIsUpdateRotator)
		{
			AttachParentComponent->SetRelativeRotation(FQuat::FastLerp(Source.GetRotation(), Source.GetRotation() + DestinationTransform.GetRotation(), DeltaTime * InterpSpeed));
		}

		if (bIsUpdateScale)
		{
			AttachParentComponent->SetRelativeLocation(FMath::VInterpTo(Source.GetLocation(), DestinationTransform.GetLocation(), DeltaTime, InterpSpeed));
		}
	}	
}

