// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveTriggerComponent.h"
#include "InteractiveScriptComponent.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UInteractiveScriptComponent : public UInteractiveTriggerComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;
};
