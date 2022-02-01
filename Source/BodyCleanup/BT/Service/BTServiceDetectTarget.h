// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BTBaseService.h"
#include "BTServiceDetectTarget.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UBTServiceDetectTarget : public UBTBaseService
{
	GENERATED_BODY()

public :
	UBTServiceDetectTarget();

protected:
	/** update next tick interval
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
