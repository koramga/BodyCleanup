// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelDesignerTools/Trigger/Classes/Actor/TriggerActorComponent.h"
#include "DamageTriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Triggers), meta=(BlueprintSpawnableComponent) )
class BODYCLEANUP_API UDamageTriggerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()

public:
	UDamageTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;

public :
	virtual void UpdateAction(const FLevelTriggerUpdateActionParam& LevelTriggerUpdateActionParam) override;	
};
