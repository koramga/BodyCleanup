// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerActorComponent.h"
#include "AttributeTriggerComponent.generated.h"

/**
 * 
 */
UCLASS()
class LEVELDESIGNERTOOLS_API UAttributeTriggerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()

public:
	UAttributeTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;
};
