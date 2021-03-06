// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveSuckingComponent.h"
#include "LevelDesignerTools/Utility/LevelSupportFunctionLibrary.h"
#include "../../../Character/BaseCharacter.h"
#include "../../../Actor/BaseActor.h"
#include "../../../GAS/Ability/BaseGameplayAbility.h"
#include "../../../GAS/Interface/Actor/GASActorInterface.h"
#include "../../../GAS/Effect/BaseGameplayEffect.h"
#include "../../../GCS/Effect/BaseCAPEffect.h"

UInteractiveSuckingComponent::UInteractiveSuckingComponent()
{
	
}

void UInteractiveSuckingComponent::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(BaseCAPEffectClass))
	{
		BaseCAPEffect = NewObject<UBaseCAPEffect>(this, BaseCAPEffectClass); 
	}

	for(EInteractiveSuckingType TriggerInteractiveSuckingType : TriggerInteractiveSuckingTypes)
	{
		AddTriggerState(static_cast<uint8>(TriggerInteractiveSuckingType));
	}

	if(IsCharacter())
	{
		PrimitiveComponents.Add(Cast<ABaseCharacter>(GetOwner())->GetMesh());
	}
	else
	{
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
			if(PrimitiveComponent.IsValid()
				&& PrimitiveComponent->IsA(UStaticMeshComponent::StaticClass()))
			{
				PrimitiveComponent->SetSimulatePhysics(true);
			}
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

				if (LinearVelocity.Size() <= 500.f)
				{
					Super::SetInteractiveType(static_cast<uint8>(EInteractiveSuckingType::None));
					SetComponentTickEnabled(false);
					SetRigidBodyCollision(false);
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
	
	//UE_LOG(LogTemp, Display, TEXT("Kormaga CanUpdateInteractive : <%s> <%s>"), *GetEnumerationToString(NextInteractiveSuckingType), *GetEnumerationToString(CurrentInteractiveSuckingType));

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

void UInteractiveSuckingComponent::SetRigidBodyCollision(bool bIsCollision)
{
	for(TSoftObjectPtr<UPrimitiveComponent> PrimitiveComponent : PrimitiveComponents)
	{
		PrimitiveComponent->SetNotifyRigidBodyCollision(bIsCollision);
	}
}

bool UInteractiveSuckingComponent::IsCharacter() const
{
	const AActor* Owner = GetOwner();

	if(Owner->IsA(ABaseCharacter::StaticClass()))
	{
		return true;
	}

	return false;
}

bool UInteractiveSuckingComponent::IsAvailableInteractiveCharacter() const
{
	const AActor* Owner = GetOwner();
	const ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Owner);
	
	if(IsValid(BaseCharacter)
		&& BaseCharacter->IsDeath())
	{
		return true;
	}

	return false;
}

EInteractiveSuckingType UInteractiveSuckingComponent::GetInteractiveSuckingType() const
{
	return static_cast<EInteractiveSuckingType>(InteractiveType);
}

bool UInteractiveSuckingComponent::SetSucking(USceneComponent* SceneComponent)
{		
	if(IsCharacter())
	{
		if(false == IsAvailableInteractiveCharacter())
		{
			return false;
		}		
	}
	
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
	if(IsCharacter())
	{
		if(false == IsAvailableInteractiveCharacter())
		{
			return false;
		}		
	}
	
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

			SetRigidBodyCollision(true);
			SetComponentTickEnabled(true);

			return true;
		}
	}

	return false;
}

bool UInteractiveSuckingComponent::SetHolding(USceneComponent* SceneComponent)
{
	if(IsCharacter())
	{
		if(false == IsAvailableInteractiveCharacter())
		{
			return false;
		}		
	}
	
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
	if(IsCharacter())
	{
		if(false == IsAvailableInteractiveCharacter())
		{
			return false;
		}		
	}
	
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
	return !bCanHolding;
}

int32 UInteractiveSuckingComponent::GetJunkValue() const
{
	return JunkValue;
}

UBaseCAPEffect* UInteractiveSuckingComponent::GetHoldShootingCAPEffect()
{
	return BaseCAPEffect;
}
