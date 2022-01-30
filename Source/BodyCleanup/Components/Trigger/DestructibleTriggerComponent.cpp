// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleTriggerComponent.h"
#include "DestructibleComponent.h"
#include "LevelDesignerTools/Utility/LevelSupportFunctionLibrary.h"

UDestructibleTriggerComponent::UDestructibleTriggerComponent()
{ 
	LevelTriggerDestructibleType = ELevelTriggerDestructibleType::Radial;
}

void UDestructibleTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDestructibleTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();

	TArray<TSoftObjectPtr<UPrimitiveComponent>> PrimitiveComponents;
	if(DestructibleInputTo.bIsTag)
	{
		ULevelSupportFunctionLibrary::FindPrimitiveComponentsByTags(PrimitiveComponents, GetOwner(), DestructibleInputTo.Names);
	}
	else
	{
		ULevelSupportFunctionLibrary::FindPrimitiveComponentsByNames(PrimitiveComponents, GetOwner(), DestructibleInputTo.Names);
	}

	for(TSoftObjectPtr<UPrimitiveComponent> PrimitiveComponent : PrimitiveComponents)
	{
		if(PrimitiveComponent->IsA(UDestructibleComponent::StaticClass()))
		{
			DestructibleComponents.Add(Cast<UDestructibleComponent>(PrimitiveComponent.Get()));
		}
	}
}

void UDestructibleTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	if(InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		FVector Location = GetOwner()->GetActorLocation();

		UE_LOG(LogTemp, Display, TEXT("koramga Destructible Mesh!"));
		
		for(const TSoftObjectPtr<UDestructibleComponent>& DestructibleComponent : DestructibleComponents)
		{
			if(DestructibleComponent.IsValid())
			{
				//DestructibleMeshComponent->ApplyDamage()
				if(ELevelTriggerDestructibleType::Radial == LevelTriggerDestructibleType)
				{
					DestructibleComponent->ApplyRadiusDamage(Damage, Location, Radius, Strength, false);
				}
				else if(ELevelTriggerDestructibleType::Linear == LevelTriggerDestructibleType)
				{
					DestructibleComponent->ApplyDamage(Damage, Location, ImpulseDir, Strength);
				}
			}
		}
	}
}
