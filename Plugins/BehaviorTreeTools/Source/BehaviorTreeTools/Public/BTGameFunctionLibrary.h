// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BTGameFunctionLibrary.generated.h"

/**
 * 
 */

class IBTCharacterInterface;
class IBTControllerInterface;

UCLASS()
class BEHAVIORTREETOOLS_API UBTGameFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public :
	static const FName TraceRangeName;
	static const FName TargetObjectName;
	static const FName LookAroundCycleTimeName;
	static const FName PhaseName;
	static const FName GoalTraceTargetRangeName;
	static const FName PatrolCooldownName;

public :
	static bool IsBTActor(const AActor* Actor);
	static bool IsBTController(const AController* Controller);
	static bool IsEnemy(const IBTControllerInterface* LHS, const IBTControllerInterface* RHS);
};
