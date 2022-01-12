// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ExDefines.h"
#include "UObject/Interface.h"
#include "LevelTriggerInterface.generated.h"

//SceneComponent->GetClass()->ImplementsInterface()

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULevelTriggerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BODYCLEANUP_API ILevelTriggerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsOnTrigger() const = 0;
	virtual void GetTriggerLocation(TArray<FVector>& TriggerLocations) = 0;
	virtual void CallTriggerObservers(bool bInputIsTick) = 0;
	virtual void AddTriggerObserver(TSoftObjectPtr<ILevelTriggerInterface> LevelTriggerInterface) = 0;
	virtual void CalledTriggerObservers(TSoftObjectPtr<UActorComponent> CallerActorComponent, bool bInputIsTick) = 0;
};
