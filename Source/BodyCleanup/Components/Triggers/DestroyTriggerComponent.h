// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TriggerComponent.h"
#include "DestroyTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class BODYCLEANUP_API UDestroyTriggerComponent : public UTriggerComponent
{
	GENERATED_BODY()

public :
	UDestroyTriggerComponent();

protected :
	bool		bIsTriggerDestroy = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private :
	UFUNCTION()
	void OnActorDestroyed(AActor* DestroyedActor);

};
