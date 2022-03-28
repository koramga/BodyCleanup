// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerActorComponent.h"
#include "StateTriggerComponent.generated.h"

/**
 * 
 */
UCLASS()
class LEVELDESIGNERTOOLS_API UStateTriggerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()

public :
	UStateTriggerComponent();
	
protected :
	TArray<uint8>	TriggerStates;

protected :
	void AddTriggerState(uint8 TriggerState);
	void RemoveTriggerState(uint8 TriggerState);
	void UpdateTriggerState(uint8 UpdateTriggerState);

};
