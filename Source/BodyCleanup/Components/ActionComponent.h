// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TriggerComponent.h"
#include "Interfaces/LevelActionInterface.h"
#include "ActionComponent.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UActionComponent : public UTriggerComponent, public ILevelActionInterface
{
	GENERATED_BODY()

public:
	virtual void OnTrigger(class ILevelTrigger* LevelTrigger, bool bIsOnTrigger) override;
};
