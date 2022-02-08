// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTaskNPCAbilityNode.h"
#include "AIController.h"
#include "Interface/BTControllerInterface.h"
#include "Interface/BTCharacterInterface.h"
#include "BTGameFunctionLibrary.h"
#include "DrawDebugHelpers.h"

UBTTaskNPCAbilityNode::UBTTaskNPCAbilityNode()
{
	NodeName = TEXT("AbilityNode");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskNPCAbilityNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (false == UBTGameFunctionLibrary::IsBTController(OwnerComp.GetAIOwner()))
	{
		return EBTNodeResult::Failed;
	}

	const IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());

	if (OwnerControllerInterface->IsDeathPossessActor())
	{
		return EBTNodeResult::Failed;
	}

	FBTAbilityInfo AbilityInfo = OwnerControllerInterface->GetAbilityInfoByTag(AbilityGameplayTag);

	if (false == AbilityInfo.CanActivate)
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UBTTaskNPCAbilityNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (false == UBTGameFunctionLibrary::IsBTController(OwnerComp.GetAIOwner()))
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());

	if (OwnerControllerInterface->IsDeathPossessActor())
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if (false == bIsActivateAbility)
	{
		if (false == OwnerControllerInterface->ActivateAbilityByTag(AbilityGameplayTag))
		{
			return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		else
		{
			bIsActivateAbility = true;
		}
	}
	else
	{
		FBTAbilityInfo AbilityInfo = OwnerControllerInterface->GetAbilityInfoByTag(AbilityGameplayTag);

		if (false == AbilityInfo.IsActivate)
		{
			bIsActivateAbility = false;
			return FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

