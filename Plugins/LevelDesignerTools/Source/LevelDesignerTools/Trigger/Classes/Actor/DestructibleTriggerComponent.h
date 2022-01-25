// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerActorComponent.h"
#include "DestructibleTriggerComponent.generated.h"

/**
 * 
 */
UCLASS()
class LEVELDESIGNERTOOLS_API UDestructibleTriggerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()

public :
	UDestructibleTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;
	
};
