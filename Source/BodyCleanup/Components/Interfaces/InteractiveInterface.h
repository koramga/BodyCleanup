// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ExDefines.h"
#include "UObject/Interface.h"
#include "InteractiveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractiveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BODYCLEANUP_API IInteractiveInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual EInteractiveAction GetInteractiveAction() const;
	virtual void SetInteractiveAction(EInteractiveAction InputInteractiveAction);
	virtual void SetInteractiveComponent(TSoftObjectPtr<USceneComponent> InputInteractiveComponent);
	virtual EInteractiveType GetInteractiveType() const;
	virtual void SetInteractiveType(EInteractiveType InputInteractiveType);
};
