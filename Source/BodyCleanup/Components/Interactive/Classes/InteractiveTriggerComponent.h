// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelDesignerTools/Trigger/Classes/Actor/StateTriggerComponent.h"
#include "../Interfaces/InteractiveComponentInterface.h"
#include "InteractiveTriggerComponent.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UInteractiveTriggerComponent : public UStateTriggerComponent, public IInteractiveComponentInterface
{
	GENERATED_BODY()
	
};
