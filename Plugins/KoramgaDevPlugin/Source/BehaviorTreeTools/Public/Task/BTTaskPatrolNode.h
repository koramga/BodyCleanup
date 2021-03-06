// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTDefines.h"
#include "Task/BTBaseTaskNode.h"
#include "BTTaskPatrolNode.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORTREETOOLS_API UBTTaskPatrolNode : public UBTBaseTaskNode
{
	GENERATED_BODY()

public :
	UBTTaskPatrolNode();

protected:
	FGameplayTag	AbilityGameplayTag;
	bool			bIsActivateAbility = false;
	EBTPatrolType	PatrolType;
	FVector			SpaceGoalPoint;

protected:
	virtual void Release(UBehaviorTreeComponent& OwnerComp, EBTNodeResult::Type InType) override;
	
protected:
	/** starts this task, should return Succeeded, Failed or InProgress
	 *  (use FinishLatentTask() when returning InProgress)
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	/** ticks this task
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
