// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../BTDefines.h"
#include "BTControllerInterface.generated.h"

UENUM(BlueprintType)
enum class ETeamType : uint8
{
	None,
	Player,
	Enemy,
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBTControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

UENUM(BlueprintType)
enum class EBlackboardVariableType : uint8
{
	Object,
	Float,
	Int32,
	FVector,
	Bool,
};

typedef TVariant<UObject*, float, int32, FVector, bool> TBlackboardVariable;

class BEHAVIORTREETOOLS_API IBTControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual ETeamType GetTeamType() const  = 0;
	virtual TBlackboardVariable GetBlackboardVariable(const FName& Name, EBlackboardVariableType BlackboardVariableType) const = 0;
	virtual bool SetBlackboardVariable(const FName& Name, const TBlackboardVariable& Variable) = 0;
	virtual bool IsDeathPossessActor() const = 0;
	virtual FVector GetCharacterLocation() const = 0;
	virtual AActor* GetPossessActor() const = 0;
	virtual bool CanMovePossessActor() const = 0;
	virtual bool CanUpdateAnimationPossessActor(uint8 InAnimationType) const = 0;
	virtual FBTAbilityInfo GetAbilityInfoByTag(const struct FGameplayTag& Tag) const = 0;
	virtual bool ActivateAbilityByTag(const struct FGameplayTag& Tag) = 0;
	virtual bool DeActivateAbilityByTag(const struct FGameplayTag& Tag) = 0;
	virtual EBTPatrolType GetPatrolType() const = 0;
	virtual class IBTPatrolActorInterface* GetPatrolActorInterface() const = 0;
	virtual FBTPatrolInfo GetPatrolInfo() const = 0;
	virtual void SetNextPatrol() = 0;
};
