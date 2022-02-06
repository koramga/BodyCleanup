// Fill out your copyright notice in the Description page of Project Settings.


#include "BTLookAroundNode.h"
#include "AIController.h"
#include "../../BT/Interface/BTControllerInterface.h"
#include "../../BT/Interface/BTCharacterInterface.h"
#include "../../Controller/Player/BasePlayerController.h"
#include "../Utility/BTGameFunctionLibrary.h"
#include "DrawDebugHelpers.h"

UBTTaskNodeLookAround::UBTTaskNodeLookAround()
{
	NodeName = TEXT("LookAround");
	bNotifyTick = true;

	AbilityGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("NPC.Ability.LookAround"));
}

EBTNodeResult::Type UBTTaskNodeLookAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(false == UBTGameFunctionLibrary::IsBTController(OwnerComp.GetAIOwner()))
	{
		return EBTNodeResult::Failed;
	}

	const IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());

	if(OwnerControllerInterface->IsDeathPossessActor())
	{
		return EBTNodeResult::Failed;
	}
	
	if(false == OwnerControllerInterface->CanActivateAbilityByTag(AbilityGameplayTag))
	{
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::InProgress;
}

void UBTTaskNodeLookAround::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	if(false == UBTGameFunctionLibrary::IsBTController(OwnerComp.GetAIOwner()))
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());

	if(OwnerControllerInterface->IsDeathPossessActor())
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if(false == bIsActivateLookAround)
	{
		if(false == OwnerControllerInterface->ActivateAbilityByTag(AbilityGameplayTag))
		{
			return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		else
		{
			bIsActivateLookAround = true;
		}		
	}
	else
	{
		if(false == OwnerControllerInterface->IsActivateAbilityByTag(AbilityGameplayTag))
		{
			bIsActivateLookAround = false;
			return FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);			
		}
	}
}