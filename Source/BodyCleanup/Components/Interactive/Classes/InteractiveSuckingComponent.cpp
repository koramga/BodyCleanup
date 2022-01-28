// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveSuckingComponent.h"
#include "LevelDesignerTools/Utility/LevelSupportFunctionLibrary.h"

void UInteractiveSuckingComponent::BeginPlay()
{
	Super::BeginPlay();

	for(EInteractiveSuckingType TriggerInteractiveSuckingType : TriggerInteractiveSuckingTypes)
	{
		AddTriggerState(static_cast<uint8>(TriggerInteractiveSuckingType));
	}

	if(Names.Num() <= 0)
	{
		ULevelSupportFunctionLibrary::FindPrimitiveComponets(PrimitiveComponents, GetOwner());
	}
	else
	{
		if(bIsTag)
		{
			ULevelSupportFunctionLibrary::FindPrimitiveComponentsByTags(PrimitiveComponents, GetOwner(), Names);
		}
		else
		{
			ULevelSupportFunctionLibrary::FindPrimitiveComponentsByNames(PrimitiveComponents, GetOwner(), Names);
		}
	}

	for(TSoftObjectPtr<UPrimitiveComponent>& PrimitiveComponent : PrimitiveComponents)
	{
		if(PrimitiveComponent.IsValid())
		{
			PrimitiveComponent->SetSimulatePhysics(true);
		}
	}
}

void UInteractiveSuckingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	EInteractiveSuckingType InteractiveSuckingType = static_cast<EInteractiveSuckingType>(InteractiveType);
	
	if (EInteractiveSuckingType::ArcShooting == InteractiveSuckingType
		|| EInteractiveSuckingType::HoldShooting == InteractiveSuckingType)
	{
		for (TSoftObjectPtr<UPrimitiveComponent> PrimitiveComponent : PrimitiveComponents)
		{
			if (PrimitiveComponent.IsValid())
			{
				FVector LinearVelocity = PrimitiveComponent->GetPhysicsLinearVelocity();

				if (LinearVelocity.Size() <= 10.f)
				{
					Super::SetInteractiveType(static_cast<uint8>(EInteractiveSuckingType::None));
					SetComponentTickEnabled(false);
				}
			}
		}
	}
	else
	{
		SetComponentTickEnabled(false);
	}
}

bool UInteractiveSuckingComponent::CanUpdateInteractiveType(uint8 CurrentInteractiveType, uint8 DesiredInteractiveType)
{
	if(false == Super::CanUpdateInteractiveType(CurrentInteractiveType, DesiredInteractiveType))
	{
		return false;
	}

	EInteractiveSuckingType CurrentInteractiveSuckingType = static_cast<EInteractiveSuckingType>(CurrentInteractiveType);
	EInteractiveSuckingType NextInteractiveSuckingType = static_cast<EInteractiveSuckingType>(DesiredInteractiveType);
	
	UE_LOG(LogTemp, Display, TEXT("Kormaga CanUpdateInteractive : <%s> <%s>"), *GetEnumerationToString(NextInteractiveSuckingType), *GetEnumerationToString(CurrentInteractiveSuckingType));

	if (EInteractiveSuckingType::ArcShooting == CurrentInteractiveSuckingType
		|| EInteractiveSuckingType::HoldShooting == CurrentInteractiveSuckingType)
	{
		return false;
	}

	return true;
}

void UInteractiveSuckingComponent::UpdateInteractiveType(uint8 CurrentInteractiveType, uint8 BeforeInteractiveType)
{
	Super::UpdateInteractiveType(CurrentInteractiveType, BeforeInteractiveType);
	
	EInteractiveSuckingType CurrentInteractiveSuckingType = static_cast<EInteractiveSuckingType>(CurrentInteractiveType);
	EInteractiveSuckingType BeforeInteractiveSuckingType = static_cast<EInteractiveSuckingType>(BeforeInteractiveType);
}

bool UInteractiveSuckingComponent::Sucking(USceneComponent* SceneComponent)
{
	EInteractiveSuckingType InteractiveSuckingType = static_cast<EInteractiveSuckingType>(InteractiveType);

	if(EInteractiveSuckingType::Sucking != InteractiveSuckingType)
	{
		if(Super::UpdateInteractiveType(static_cast<uint8>(EInteractiveSuckingType::Sucking)))
		{
			InteractiveSuckingType = static_cast<EInteractiveSuckingType>(InteractiveType);
		}
	}

	if(EInteractiveSuckingType::Sucking == InteractiveSuckingType)
	{
		for(TSoftObjectPtr<UPrimitiveComponent> PrimitiveComponent : PrimitiveComponents)
		{
			if(PrimitiveComponent.IsValid())
			{
				const FTransform& Transform = PrimitiveComponent->GetComponentTransform();
				FVector Direction = SceneComponent->GetComponentToWorld().GetLocation() - PrimitiveComponent->GetComponentToWorld().GetLocation();
				Direction.Normalize();
				PrimitiveComponent->SetPhysicsLinearVelocity(Direction * SuckingPower);				
			}
		}

		return true;
	}

	return false;
}

bool UInteractiveSuckingComponent::Shooting(USceneComponent* SceneComponent)
{
	EInteractiveSuckingType InteractiveSuckingType = static_cast<EInteractiveSuckingType>(InteractiveType);

	if(EInteractiveSuckingType::Holding == InteractiveSuckingType)
	{
		if(Super::UpdateInteractiveType(static_cast<uint8>(EInteractiveSuckingType::HoldShooting)))
		{
			for(TSoftObjectPtr<UPrimitiveComponent> PrimitiveComponent : PrimitiveComponents)
			{
				if(PrimitiveComponent.IsValid())
				{
					PrimitiveComponent->SetPhysicsLinearVelocity(SceneComponent->GetOwner()->GetActorForwardVector() * HoldShootingPower);				
				}
			}

			SetComponentTickEnabled(true);

			return true;
		}
	}

	return false;
}

bool UInteractiveSuckingComponent::Holding(USceneComponent* SceneComponent)
{
	EInteractiveSuckingType InteractiveSuckingType = static_cast<EInteractiveSuckingType>(InteractiveType);

	if(EInteractiveSuckingType::Holding != InteractiveSuckingType)
	{
		if(Super::UpdateInteractiveType(static_cast<uint8>(EInteractiveSuckingType::Holding)))
		{
			InteractiveSuckingType = static_cast<EInteractiveSuckingType>(InteractiveType);
		}
	}
	
	if(EInteractiveSuckingType::Holding == InteractiveSuckingType)
	{
		return true;
	}

	return false;
}

bool UInteractiveSuckingComponent::IsJunk() const
{
	if(JunkValue <= 0)
	{
		return false;
	}

	return true;
}
