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
class BODYCLEANUP_API UBTGameFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public :
	static const FName TraceRangeName;
	static const FName LookAroundTimeName;
	static const FName TargetObjectName;
	static const FName LookAroundCycleTimeName;

public :
	static bool IsBTActor(const AActor* Actor);
	static bool IsBTController(const AController* Controller);
	static bool IsEnemy(const IBTControllerInterface* LHS, const IBTControllerInterface* RHS);
	
};
