// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Assist/LevelTriggerActorAssist.h"
#include "LevelToolsActor.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULevelToolsActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEVELDESIGNERTOOLS_API ILevelToolsActor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual class ULevelTriggerActorAssist* GetLevelTriggerActorAssist() const = 0;
};