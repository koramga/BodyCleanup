// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interfaces/LevelTriggerInterface.h"

/**
 * 
 */
class BODYCLEANUP_API CLevelTriggerImplementation
	: public ILevelTriggerInterface
{
public:
	CLevelTriggerImplementation();
	~CLevelTriggerImplementation();

public:
	virtual bool IsOnTrigger() const override;
	virtual void GetTriggerLocation(TArray<FVector>& TriggerLocations) override;
	virtual void CallTriggerObservers(bool bInputIsTick) override;
	virtual void AddTriggerObserver(TSoftObjectPtr<ILevelTriggerInterface> LevelTriggerInterface) override;
	virtual void CalledTriggerObservers(TSoftObjectPtr<USceneComponent> CallerActorComponent, bool bInputIsTick) override;

};
