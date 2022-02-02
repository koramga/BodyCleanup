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
}

EBTNodeResult::Type UBTTaskNodeLookAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(false == UBTGameFunctionLibrary::IsBTController(OwnerComp.GetAIOwner()))
	{
		return EBTNodeResult::Failed;
	}

	const IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());

	if(OwnerControllerInterface->IsDeathPossessActor())
	{
		return EBTNodeResult::Failed;
	}

	TBlackboardVariable LookAroundBlackboardVariable = OwnerControllerInterface->GetBlackboardVariable(UBTGameFunctionLibrary::LookAroundTimeName, EBlackboardVariableType::Float);

	if(LookAroundBlackboardVariable.Get<float>() <= 0.f)
	{
		return EBTNodeResult::Failed;
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

void UBTTaskNodeLookAround::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}