// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CapabilitySystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCapabilitySystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMECAPABILITYSYSTEM_API ICapabilitySystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual class UCapabilitySystemComponent* GetCapabilitySystemComponent() const = 0;
};
