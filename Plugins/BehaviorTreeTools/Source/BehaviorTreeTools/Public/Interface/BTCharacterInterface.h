// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../BTDefines.h"
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
class BEHAVIORTREETOOLS_API IBTCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsDeath() const = 0;
	virtual bool ActivateAbilityByTag(const struct FGameplayTag& Tag) = 0;
	virtual bool DeActivateAbilityByTag(const struct FGameplayTag& Tag) = 0;
	virtual FBTAbilityInfo GetAbilityInfoByTag(const struct FGameplayTag& Tag) const = 0;
	virtual EBTPatrolType GetPatrolType() const = 0;
	virtual class IBTPatrolActorInterface* GetPatrolActorInterface() const = 0;
	virtual void SetNextPatrol() = 0;
};
