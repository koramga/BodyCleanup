// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskTraceTargetNode.h"
#include "AIController.h"
#include "../../BT/Interface/BTControllerInterface.h"
#include "../../BT/Interface/BTCharacterInterface.h"
#include "../../Controller/Player/BasePlayerController.h"
#include "../Utility/BTGameFunctionLibrary.h"

UBTTaskTraceTargetNode::UBTTaskTraceTargetNode()
{
	NodeName = TEXT("TraceTarget");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskTraceTargetNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	AAIController* OwnerAIController = OwnerComp.GetAIOwner();

	if(false == UBTGameFunctionLibrary::IsBTController(OwnerComp.GetAIOwner()))
	{
		return EBTNodeResult::Failed;
	}

	const IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());
	
	if(OwnerControllerInterface->IsDeathPossessActor())
	{
		return EBTNodeResult::Failed;
	}

	if(false == OwnerControllerInterface->CanMovePossessActor())
	{
		return EBTNodeResult::Failed;
	}

	TBlackboardVariable BlackboardTargetVariable = OwnerControllerInterface->GetBlackboardVariable(UBTGameFunctionLibrary::TargetObjectName, EBlackboardVariableType::Object);

	IBTControllerInterface* TargetControllerInterface = Cast<IBTControllerInterface>(BlackboardTargetVariable.Get<UObject*>());

	if(TargetControllerInterface == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	if(TargetControllerInterface->IsDeathPossessActor())
	{
		return EBTNodeResult::Failed;
	}

	TBlackboardVariable GoalTraceTargetRangeName = OwnerControllerInterface->GetBlackboardVariable(UBTGameFunctionLibrary::GoalTraceTargetRangeName, EBlackboardVariableType::Float);

	if(IsGoalActor(OwnerControllerInterface->GetPossessActor(), TargetControllerInterface->GetPossessActor(), GoalTraceTargetRangeName.Get<float>()))
	{
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::InProgress;
}

void UBTTaskTraceTargetNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* OwnerAIController = OwnerComp.GetAIOwner();
	const IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());

	if(OwnerControllerInterface->IsDeathPossessActor())
	{
		OwnerAIController->StopMovement();
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if(false == OwnerControllerInterface->CanMovePossessActor())
	{
		OwnerAIController->StopMovement();
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}	

	TBlackboardVariable BlackboardTargetVariable = OwnerControllerInterface->GetBlackboardVariable(UBTGameFunctionLibrary::TargetObjectName, EBlackboardVariableType::Object);

	IBTControllerInterface* TargetControllerInterface = Cast<IBTControllerInterface>(BlackboardTargetVariable.Get<UObject*>());

	if(TargetControllerInterface == nullptr)
	{
		OwnerAIController->StopMovement();
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if(TargetControllerInterface->IsDeathPossessActor())
	{
		OwnerAIController->StopMovement();
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	TBlackboardVariable GoalTraceTargetRangeName = OwnerControllerInterface->GetBlackboardVariable(UBTGameFunctionLibrary::GoalTraceTargetRangeName, EBlackboardVariableType::Float);
	
	if(IsGoalActor(OwnerControllerInterface->GetPossessActor(), TargetControllerInterface->GetPossessActor(), GoalTraceTargetRangeName.Get<float>()))
	{
		OwnerAIController->StopMovement();
		return FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	OwnerAIController->MoveToLocation(TargetControllerInterface->GetPossessActor()->GetActorLocation());
}
