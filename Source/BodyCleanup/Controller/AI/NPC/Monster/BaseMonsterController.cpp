// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonsterController.h"

ABaseMonsterController::ABaseMonsterController()
{
	TeamType = ETeamType::Enemy;
}

void ABaseMonsterController::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ABaseMonsterController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABaseMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}