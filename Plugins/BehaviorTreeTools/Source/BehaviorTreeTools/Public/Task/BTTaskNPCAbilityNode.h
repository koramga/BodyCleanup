// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTBaseTaskNode.h"
#include "BTTaskNPCAbilityNode.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORTREETOOLS_API UBTTaskNPCAbilityNode : public UBTBaseTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNPCAbilityNode();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag	AbilityGameplayTag;


	bool			bIsActivateAbility = false;

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
