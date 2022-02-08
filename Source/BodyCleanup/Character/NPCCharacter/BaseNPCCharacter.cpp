// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNPCCharacter.h"
#include "Interface/BTPatrolActorInterface.h"
#include "../../Actor/Level/Patrol/BasePatrolActor.h"

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

EBTPatrolType ABaseNPCCharacter::GetPatrolType() const
{
	if(PatrolActors.Num() <= 1)
	{
		return EBTPatrolType::None;
	}
	
	return PatrolType;
}

IBTPatrolActorInterface* ABaseNPCCharacter::GetPatrolActorInterface() const
{
	if(PatrolActors.Num() <= 1)
	{
		return nullptr;
	}

	return Cast<IBTPatrolActorInterface>(PatrolActors[PatrolActorIndex]);
}

void ABaseNPCCharacter::SetNextPatrol()
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
