// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicMovementComponent.h"

UDynamicMovementComponent::UDynamicMovementComponent()
{

}

void UDynamicMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (EActionComponentToType::Parent == ActionComponentToType)
	{
		USceneComponent* AttachParentComponent = GetAttachParent();

		if (IsValid(AttachParentComponent))
		{
			DynamicMovementParams.Add(FDynamicMovementParam(AttachParentComponent));
		}
	}
	else if (EActionComponentToType::Setup == ActionComponentToType)
	{
		if (ENameType::Name == NameType)
		{
			USceneComponent* ComponentByName = FindComponentByName(GetOwner()->GetRootComponent(), ActionName);

			if (IsValid(ComponentByName))
			{
				DynamicMovementParams.Add(FDynamicMovementParam(ComponentByName));
			}
		}
		else if (ENameType::Tag == NameType)
		{
			TArray<TSoftObjectPtr<USceneComponent>> SceneComponents;

			FindComponentByTriggreName(SceneComponents, GetOwner(), ActionName);

			for (TSoftObjectPtr<USceneComponent> SceneComponent : SceneComponents)
			{
				DynamicMovementParams.Add(FDynamicMovementParam(SceneComponent));
			}
		}
	}

	for (FDynamicMovementParam& DynamicMovementParam : DynamicMovementParams)
	{
		DynamicMovementParam.MovementComponent->Mobility = EComponentMobility::Type::Movable;

		FTransform InputTransform = DynamicMovementParam.MovementComponent->GetRelativeTransform();

		for (const FTransform& DestinationDeltaTransform : DestinationDeltaTransforms)
		{
			InputTransform.SetRotation((InputTransform.GetRotation() + DestinationDeltaTransform.GetRotation()));
			InputTransform.SetLocation(InputTransform.GetLocation() + DestinationDeltaTransform.GetLocation());
			InputTransform.SetScale3D(InputTransform.GetScale3D() + DestinationDeltaTransform.GetScale3D());

			DynamicMovementParam.Transforms.Add(InputTransform);
		}
	}
}

void UDynamicMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (FDynamicMovementParam& DynamicMovementParam : DynamicMovementParams)
	{
		if (DynamicMovementParam.MovementComponent.IsValid())
		{
			FTransform Source = DynamicMovementParam.MovementComponent->GetRelativeTransform();
			const FTransform& DestinationTransform = DynamicMovementParam.Transforms[ComponentMovementIndex];

			if (bIsUpdateScale)
			{
				DynamicMovementParam.MovementComponent->SetRelativeScale3D(FMath::VInterpTo(Source.GetScale3D(), DestinationTransform.GetScale3D(), DeltaTime, InterpSpeed));
			}

			if (bIsUpdateRotator)
			{
				DynamicMovementParam.MovementComponent->SetRelativeRotation(FQuat::FastLerp(Source.GetRotation(), Source.GetRotation() + DestinationTransform.GetRotation(), DeltaTime * InterpSpeed));
			}

			if (bIsUpdateLocation)
			{
				DynamicMovementParam.MovementComponent->SetRelativeLocation(FMath::VInterpTo(Source.GetLocation(), DestinationTransform.GetLocation(), DeltaTime, InterpSpeed));
			}
		}
	}
}

void UDynamicMovementComponent::OnTrigger(bool bInputIsOnTrigger)
{
	Super::OnTrigger(bInputIsOnTrigger);

	if (bInputIsOnTrigger)
	{
		if (EDynamicMovementCycleType::Cycle == DynamicMovementCycleType)
		{
			ComponentMovementIndex = (ComponentMovementIndex + 1) % (DestinationDeltaTransforms.Num() + 1);
		}
		else
		{
			if (ReverseSign > 0)
			{
				if (DestinationDeltaTransforms.Num() + 1 <= ComponentMovementIndex + 1)
				{
					ReverseSign *= -1;
				}
			}
			else if(ReverseSign < 0)
			{
				if (ComponentMovementIndex - 1 < 0)
				{
					ReverseSign *= -1;
				}
			}

			ComponentMovementIndex += ReverseSign;
		}
	}
}
