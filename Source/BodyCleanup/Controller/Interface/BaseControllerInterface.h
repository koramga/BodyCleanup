// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BaseControllerInterface.generated.h"

UENUM(BlueprintType)
enum class ETeamType : uint8
{
	None,
	Player,
	Enemy,
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBaseControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BODYCLEANUP_API IBaseControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual ETeamType GetTeamType() const  = 0;
};
