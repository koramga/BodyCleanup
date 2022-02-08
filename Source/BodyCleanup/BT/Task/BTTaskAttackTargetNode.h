// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTBaseTaskNode.h"
#include "BTTaskAttackTargetNode.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UBTTaskAttackTargetNode : public UBTBaseTaskNode
{
	GENERATED_BODY()

public :
	UBTTaskAttackTargetNode();
	
protected:
	FGameplayTag	AbilityGameplayTag;
	bool			bIsActivateAttack = false;

protected:
	/** starts this task, should return Succeeded, Failed or InProgress
	 *  (use FinishLatentTask() when returning InProgress)
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	/** ticks this task
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	
};
