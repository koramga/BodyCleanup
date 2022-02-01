// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceDetectTarget.h"
#include "../../Character/BaseCharacter.h"
#include "../../Controller/AI/BaseAIController.h"
#include "../../BT/Interface/BTControllerInterface.h"
#include "../../Controller/Player/BasePlayerController.h"

UBTServiceDetectTarget::UBTServiceDetectTarget()
{
	Interval = 0.5f;
	NodeName = TEXT("DetectTarget");
}

void UBTServiceDetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* OwnerAIController = OwnerComp.GetAIOwner();
	
	if(OwnerAIController->GetClass()->ImplementsInterface(UBTControllerInterface::StaticClass()))
	{
		return;
	}
	
	IBTControllerInterface* AIOwner = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());

	ABaseCharacter* OwnerAICharacter = Cast<ABaseCharacter>(OwnerAIController->GetPawn());	
}