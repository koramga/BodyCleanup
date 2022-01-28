// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../ExDefines.h"
#include "UObject/Interface.h"
#include "InteractiveComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractiveComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class BODYCLEANUP_API IInteractiveComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool UpdateInteractiveType(uint8 InputInteractiveType) = 0;
	virtual uint8 GetInteractiveType() const = 0;
	virtual bool CanUpdateInteractiveType(uint8 InputInteractiveType) = 0;
	
};
