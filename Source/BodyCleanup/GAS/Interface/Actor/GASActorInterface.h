// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GASActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGASActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BODYCLEANUP_API IGASActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AddAbility(const TSubclassOf<class UBaseGameplayAbility>& AbilityToGet, int32 AbilityLevel) = 0;
	virtual void AddAttributeSet(const TSubclassOf<class UBaseAttributeSet>& AttributeSet) = 0;
};
