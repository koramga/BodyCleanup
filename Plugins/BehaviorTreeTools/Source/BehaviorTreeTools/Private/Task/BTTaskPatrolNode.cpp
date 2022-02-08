// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTaskPatrolNode.h"
#include "AIController.h"
#include "Interface/BTControllerInterface.h"
#include "Interface/BTCharacterInterface.h"
#include "BTGameFunctionLibrary.h"
#include "Interface/BTPatrolActorInterface.h"

UBTTaskPatrolNode::UBTTaskPatrolNode()
{
	NodeName = TEXT("PatrolNode");
	bNotifyTick = true;
	AbilityGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("NPC.Ability.Patrol"));
}


void UBTTaskPatrolNode::Release(UBehaviorTreeComponent& OwnerComp, EBTNodeResult::Type InType)
{
	IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());
	OwnerControllerInterface->DeActivateAbilityByTag(AbilityGameplayTag);

	if(bIsActivateAbility)
	{
		bIsActivateAbility = false;
		OwnerControllerInterface->DeActivateAbilityByTag(AbilityGameplayTag);
	}
	
	Super::Release(OwnerComp, InType);
}

EBTNodeResult::Type UBTTaskPatrolNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(false == IsAvailableController(OwnerComp.GetAIOwner()))
	{
		return EBTNodeResult::Failed; 
	}

	const IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());

	if(EBTPatrolType::None == OwnerControllerInterface->GetPatrolType())
	{
		return EBTNodeResult::Failed;
	}
	
	FBTAbilityInfo AbilityInfo = OwnerControllerInterface->GetAbilityInfoByTag(AbilityGameplayTag);

	if(false == AbilityInfo.CanActivate)
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UBTTaskPatrolNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	AAIController* OwnerAIController = OwnerComp.GetAIOwner();
	IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());

	if(OwnerControllerInterface->IsDeathPossessActor())
	{
		return Release(OwnerComp, EBTNodeResult::Failed);
	}

	IBTPatrolActorInterface* PatrolActorInterface = OwnerControllerInterface->GetPatrolActorInterface();

	if(nullptr == PatrolActorInterface)
	{
		return Release(OwnerComp, EBTNodeResult::Failed);
	}

	TBlackboardVariable BlackboardTargetVariable = OwnerControllerInterface->GetBlackboardVariable(UBTGameFunctionLibrary::TargetObjectName, EBlackboardVariableType::Object);
	
	IBTControllerInterface* TargetControllerInterface = Cast<IBTControllerInterface>(BlackboardTargetVariable.Get<UObject*>());

	if(TargetControllerInterface != nullptr)
	{
		return Release(OwnerComp, EBTNodeResult::Failed);
	}

	if(false == bIsActivateAbility)
	{
		bIsActivateAbility = true;
		OwnerControllerInterface->ActivateAbilityByTag(AbilityGameplayTag);
	}

	if(PatrolActorInterface->IsGoal(OwnerControllerInterface->GetPossessActor()))
	{
		OwnerControllerInterface->SetNextPatrol();
		return Release(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		OwnerAIController->MoveToLocation(PatrolActorInterface->GetGoalPosition());
	}
}
