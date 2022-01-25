// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelTriggerActorAssist.generated.h"

/**
 * 
 */

class ILevelTriggerInterface;

enum class ELevelTriggerActorState
{
	Death,
};

UCLASS()
class LEVELDESIGNERTOOLS_API ULevelTriggerActorAssist : public UObject
{
	GENERATED_BODY()

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UObject>>		LevelTriggerInterfaces;
	
public :
	void RegisterTrigger(ILevelTriggerInterface* LevelTriggerInterface);

public :
	void SetLevelTriggerState(ELevelTriggerActorState LevelTriggerActorState, bool bIsState);
};
