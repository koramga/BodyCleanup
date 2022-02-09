// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTBaseTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORTREETOOLS_API UBTBaseTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public :
	UBTBaseTaskNode();

protected :
	bool IsGoalActor(class AActor* Source, class AActor* Target, float Radius, bool bIsDebugDrawing = false) const;
	bool IsAvailableController(AAIController* InAIController) const;

protected :
	virtual void Release(UBehaviorTreeComponent& OwnerComp, EBTNodeResult::Type InType);

protected:
	/** starts this task, should return Succeeded, Failed or InProgress
	 *  (use FinishLatentTask() when returning InProgress)
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	/** ticks this task
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	
};
