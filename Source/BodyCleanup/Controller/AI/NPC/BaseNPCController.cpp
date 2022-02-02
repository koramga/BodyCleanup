// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNPCController.h"
#include "../../../BT/Utility/BTGameFunctionLibrary.h"

ABaseNPCController::ABaseNPCController()
{
	
}

void ABaseNPCController::InitializeBlackboardData()
{
	Super::InitializeBlackboardData();
	
	TBlackboardVariable TraceRangeVariable;
	TraceRangeVariable.Set<float>(LookAroundTime.GetMetaVariable().Get<float>());

	SetBlackboardVariable(UBTGameFunctionLibrary::LookAroundTimeName, TraceRangeVariable);
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
