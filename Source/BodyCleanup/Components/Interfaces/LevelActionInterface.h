// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ExDefines.h"
#include "UObject/Interface.h"
#include "LevelActionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULevelActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BODYCLEANUP_API ILevelActionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnTrigger(bool bIsOnTrigger) = 0;
};
