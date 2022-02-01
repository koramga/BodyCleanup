// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerAIController.h"

ABasePlayerAIController::ABasePlayerAIController()
{
	TeamType = ETeamType::Player;
}

void ABasePlayerAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ABasePlayerAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABasePlayerAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
