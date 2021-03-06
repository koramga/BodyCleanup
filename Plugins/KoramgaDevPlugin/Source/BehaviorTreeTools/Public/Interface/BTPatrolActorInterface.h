// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BTPatrolActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBTPatrolActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BEHAVIORTREETOOLS_API IBTPatrolActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsGoal(const AActor* InActor) const = 0;
	virtual FVector GetGoalPosition() const = 0;
	virtual bool IsPointInActor(const FVector& InVector) const = 0;
};
