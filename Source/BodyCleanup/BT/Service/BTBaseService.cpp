// Fill out your copyright notice in the Description page of Project Settings.


#include "BTBaseService.h"


UBTBaseService::UBTBaseService()
{
}

void UBTBaseService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
