// Fill out your copyright notice in the Description page of Project Settings.


#include "BTAttackTargetNode.h"
#include "AIController.h"
#include "../../BT/Interface/BTControllerInterface.h"
#include "../../BT/Interface/BTCharacterInterface.h"
#include "../../Controller/Player/BasePlayerController.h"
#include "../Utility/BTGameFunctionLibrary.h"

UBTAttackTargetNode::UBTAttackTargetNode()
{
	NodeName = TEXT("AttackTarget");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTAttackTargetNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	AAIController* OwnerAIController = OwnerComp.GetAIOwner();

	if(false == UBTGameFunctionLibrary::IsBTController(OwnerComp.GetAIOwner()))
	{
		return EBTNodeResult::Failed;
	}

	IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());
	
	TBlackboardVariable BlackboardTargetVariable = OwnerControllerInterface->GetBlackboardVariable(UBTGameFunctionLibrary::TargetObjectName, EBlackboardVariableType::Object);

	if(OwnerControllerInterface->IsDeathPossessActor())
	{
		return EBTNodeResult::Failed;
	}
	
	IBTControllerInterface* TargetControllerInterface = Cast<IBTControllerInterface>(BlackboardTargetVariable.Get<UObject*>());

	if(TargetControllerInterface == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	if(TargetControllerInterface->IsDeathPossessActor())
	{
		return EBTNodeResult::Failed;
	}

	TBlackboardVariable TraceTargetRangeVariable;
	TraceTargetRangeVariable.Set<float>(200.f);
	
	if(false == IsGoalActor(OwnerControllerInterface->GetPossessActor(), TargetControllerInterface->GetPossessActor(), TraceTargetRangeVariable.Get<float>()))
	{
		OwnerControllerInterface->SetBlackboardVariable(UBTGameFunctionLibrary::GoalTraceTargetRangeName, TraceTargetRangeVariable);
		return EBTNodeResult::Failed;
	}
	
	TBlackboardVariable BlackboardVariable = OwnerControllerInterface->GetBlackboardVariable(UBTGameFunctionLibrary::PhaseName, EBlackboardVariableType::Int32);
	int32 Phase = BlackboardVariable.Get<int32>();

	for(int i = 0; i < 5; ++i)
	{
		FString AttackAbilityTag = FString::Printf(TEXT("NPC.Attack.%d.%d"), Phase, i);

		FGameplayTag GameplayTag = FGameplayTag::RequestGameplayTag(FName(AttackAbilityTag));
		
		if(true == OwnerControllerInterface->CanActivateAbilityByTag(GameplayTag))
		{
			AbilityGameplayTag = GameplayTag;
			return EBTNodeResult::InProgress;
		}
	}
	
	return EBTNodeResult::Failed;
}

void UBTAttackTargetNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* OwnerAIController = OwnerComp.GetAIOwner();
	IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());

	if(OwnerControllerInterface->IsDeathPossessActor())
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if(false == bIsActivateAttack)
	{
		if(false == OwnerControllerInterface->ActivateAbilityByTag(AbilityGameplayTag))
		{
			return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		else
		{
			bIsActivateAttack = true;
		}		
	}
	else
	{
		if(false == OwnerControllerInterface->IsActivateAbilityByTag(AbilityGameplayTag))
		{
			bIsActivateAttack = false;
			return FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);			
		}
	}
}
