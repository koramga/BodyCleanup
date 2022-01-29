// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveSuckingComponent.h"
#include "LevelDesignerTools/Utility/LevelSupportFunctionLibrary.h"
#include "../../../Character/BaseCharacter.h"
#include "../../../Actor/BaseActor.h"
#include "../../../GAS/Ability/BaseGameplayAbility.h"
#include "../../../GAS/Interface/Actor/GASActorInterface.h"

UInteractiveSuckingComponent::UInteractiveSuckingComponent()
{

}

void UInteractiveSuckingComponent::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(BaseGameplayAbilityClass))
	{
		AActor* Actor = GetOwner();

		if(Actor->GetClass()->ImplementsInterface(UGASActorInterface::StaticClass()))
		{
			Cast<IGASActorInterface>(Actor)->AddAbility(BaseGameplayAbilityClass, 0);	
		}
	}

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

EInteractiveSuckingType UInteractiveSuckingComponent::GetInteractiveSuckingType() const
{
	return static_cast<EInteractiveSuckingType>(InteractiveType);
}

bool UInteractiveSuckingComponent::SetSucking(USceneComponent* SceneComponent)
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

bool UInteractiveSuckingComponent::SetHoldShooting(USceneComponent* SceneComponent)
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

bool UInteractiveSuckingComponent::SetHolding(USceneComponent* SceneComponent)
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

bool UInteractiveSuckingComponent::SetNone(USceneComponent* SceneComponent)
{
	EInteractiveSuckingType InteractiveSuckingType = static_cast<EInteractiveSuckingType>(InteractiveType);

	if(EInteractiveSuckingType::None != InteractiveSuckingType)
	{
		if(Super::UpdateInteractiveType(static_cast<uint8>(EInteractiveSuckingType::None)))
		{
			InteractiveSuckingType = static_cast<EInteractiveSuckingType>(InteractiveType);
		}
	}
	
	if(EInteractiveSuckingType::None == InteractiveSuckingType)
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

int32 UInteractiveSuckingComponent::GetJunkValue() const
{
	return JunkValue;
}

const TSubclassOf<UBaseGameplayAbility>& UInteractiveSuckingComponent::GetHoldShootingAbility() const
{
	return BaseGameplayAbilityClass;
}
