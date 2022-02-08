// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNPCController.h"
#include "BTGameFunctionLibrary.h"

ABaseNPCController::ABaseNPCController()
{
	
}

void ABaseNPCController::InitializeBlackboardData()
{
	Super::InitializeBlackboardData();
}

void ABaseNPCController::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseNPCController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ABaseNPCController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABaseNPCController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}