// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerActorComponent.h"
#include "HitTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API UHitTriggerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()

public:
	UHitTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public :
	virtual void UpdateAction(const FLevelTriggerUpdateActionParam& LevelTriggerUpdateActionParam) override;
};
