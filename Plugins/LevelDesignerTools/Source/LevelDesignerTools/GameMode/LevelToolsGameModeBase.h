// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../Trigger/Managers/LevelTriggerManager.h"
#include "LevelToolsGameModeBase.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULevelToolsGameModeBase : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEVELDESIGNERTOOLS_API ILevelToolsGameModeBase
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	virtual void InitTrigger() = 0;

public:
	virtual void RegisterTrigger(class ILevelTriggerInterface* LevelTriggerInterface) = 0;
	virtual const ULevelTriggerManager* GetLevelTriggerManager() const = 0;
	virtual void UpdateTrigger(class ILevelTriggerInterface* LevelTriggerInterface, bool bInputIsOnTrigger, bool bIsCallSelf) = 0;
	virtual void UpdateTriggerOnce(class ILevelTriggerInterface* LevelTriggerInterface, bool bIsCallSelf) = 0;
};
