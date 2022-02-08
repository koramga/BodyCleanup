// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTBaseService.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORTREETOOLS_API UBTBaseService : public UBTService
{
	GENERATED_BODY()

public :
	UBTBaseService();

protected:
	/** update next tick interval
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
