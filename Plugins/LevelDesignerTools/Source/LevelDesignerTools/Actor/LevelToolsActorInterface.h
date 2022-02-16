// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Assist/LevelTriggerActorAssist.h"
#include "LevelToolsActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULevelToolsActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEVELDESIGNERTOOLS_API ILevelToolsActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual class ULevelTriggerActorAssist* GetLevelTriggerActorAssist() const = 0;
	virtual void SetDestroyFromTrigger() = 0;
};