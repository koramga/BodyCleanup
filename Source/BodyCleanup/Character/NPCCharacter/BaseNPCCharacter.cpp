// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNPCCharacter.h"
#include "Interface/BTPatrolActorInterface.h"
#include "../../Actor/Level/Patrol/BasePatrolActor.h"
#include "Components/CapsuleComponent.h"
#include "LevelDesignerTools/Utility/LevelSupportFunctionLibrary.h"

ABaseNPCCharacter::ABaseNPCCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	PatrolType = EBTPatrolType::None;
}

void ABaseNPCCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseNPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseNPCCharacter::UpdateDeath(bool bInIsDeath)
{
	Super::UpdateDeath(bInIsDeath);

	if(true == bInIsDeath)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);

		TArray<TSoftObjectPtr<UPrimitiveComponent>> PrimitiveComponents;
		
		ULevelSupportFunctionLibrary::FindPrimitiveComponets(PrimitiveComponents, this);
	}
}

EBTPatrolType ABaseNPCCharacter::GetPatrolType() const
{
	if(EBTPatrolType::Point == PatrolType)
	{
		if(PatrolActors.Num() <= 1)
		{
			return EBTPatrolType::None;
		}		
	}
	else if(EBTPatrolType::Space == PatrolType)
	{
		if(PatrolActors.Num() <= 0)
		{
			return EBTPatrolType::None;
		}
	}
		
	return PatrolType;
}

IBTPatrolActorInterface* ABaseNPCCharacter::GetPatrolActorInterface() const
{
	if(EBTPatrolType::None == PatrolType)
	{
		return nullptr;
	}
	else if(EBTPatrolType::Point == PatrolType)
	{
		if(PatrolActors.Num() <= 1)
		{
			return nullptr;
		}		
	}
	else if(EBTPatrolType::Space == PatrolType)
	{
		if(PatrolActors.Num() <= 0)
		{
			return nullptr;
		}
	}

	return Cast<IBTPatrolActorInterface>(PatrolActors[PatrolActorIndex]);
}

void ABaseNPCCharacter::SetNextPatrol()
{
	if(EBTPatrolType::Point == PatrolType)
	{
		if(PatrolActors.Num() >= 2)
		{
			PatrolActorIndex += PatrolActorDirection;

			if(PatrolActorDirection < 0)
			{
				if(PatrolActorIndex < 0)
				{
					PatrolActorIndex = 1;
					PatrolActorDirection *= -1;
				}
			}
			else if(PatrolActorDirection > 0)
			{
				if(PatrolActorIndex >= PatrolActors.Num())
				{
					PatrolActorIndex = PatrolActors.Num() - 2;
					PatrolActorDirection *= -1;
				}
			}
		}		
	}
}

FBTPatrolInfo ABaseNPCCharacter::GetPatrolInfo() const
{
	FBTPatrolInfo PatrolInfo = Super::GetPatrolInfo();

	PatrolInfo.MinDistance = MinPatrolDistance.GetMetaVariable().Get<float>();
	PatrolInfo.MaxDistance = MaxPatrolDistance.GetMetaVariable().Get<float>();

	return PatrolInfo;
}
