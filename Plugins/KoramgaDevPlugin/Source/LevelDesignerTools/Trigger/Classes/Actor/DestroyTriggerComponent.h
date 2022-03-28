// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TriggerActorComponent.h"
#include "DestroyTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API UDestroyTriggerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()

public :
	UDestroyTriggerComponent();

protected :
	bool		bIsTriggerDestroy = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;

private :
	UFUNCTION()
	void OnActorDestroyed(AActor* Actor, EEndPlayReason::Type EndPlayReason);

};
