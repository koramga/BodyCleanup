// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

ABaseAIController::ABaseAIController()
{
	TeamType = ETeamType::None;
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	UE_LOG(LogTemp, Display, TEXT("koramga : <%s> OnPossess"), *InPawn->GetName());
	
	if(IsValid(BehaviorTree)
		&& IsValid(BlackboardData))
	{
		if(false == UseBlackboard(BlackboardData, Blackboard))
		{
			UE_LOG(LogTemp, Display, TEXT("ABaseAIController::OnPossess UseBlackboard Failed.."));
			return;			
		}
		
		if (false == RunBehaviorTree(BehaviorTree))
		{
			UE_LOG(LogTemp, Display, TEXT("ABaseAIController::OnPossess RunBehaviorTree Failed.."));
			return;
		}

		UE_LOG(LogTemp, Display, TEXT("AI OnPossess Success"));
	}
	
	Super::OnPossess(InPawn);
}

void ABaseAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ETeamType ABaseAIController::GetTeamType() const
{
	return TeamType;
}
