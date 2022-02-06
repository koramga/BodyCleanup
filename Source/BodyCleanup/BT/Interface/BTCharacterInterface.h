// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BTCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBTCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BODYCLEANUP_API IBTCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsDeath() const = 0;
	virtual bool CanActivateAbilityByTag(const struct FGameplayTag& Tag) const = 0;
	virtual bool ActivateAbilityByTag(const struct FGameplayTag& Tag) = 0;
	virtual bool IsActivateAbilityByTag(const struct FGameplayTag& Tag) const = 0;
};
