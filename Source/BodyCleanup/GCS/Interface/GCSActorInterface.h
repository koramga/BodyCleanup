// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GCSActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGCSActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BODYCLEANUP_API IGCSActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AddAttributeSet(TSubclassOf<class UCAPAttributeSet> CAPAttributeSetClass) = 0;
	virtual void AddAbility(TSubclassOf<class UCAPAbility> CAPAbilityClass) = 0;
	virtual void RemoveAbility(TSubclassOf<class UCAPAbility> CAPAbilityClass) = 0;
	virtual bool IsDeath() const = 0;
};
