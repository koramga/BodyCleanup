// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNPCCharacter.h"

ABaseNPCCharacter::ABaseNPCCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	PatrolType = ENPCPatrolType::None;
}

void ABaseNPCCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseNPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}