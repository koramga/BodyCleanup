// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LevelMarkupInterface.generated.h"

UENUM(BlueprintType)
enum class ELevelMarkupType : uint8
{
	Point,
	Velocity,
	Camera,
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULevelMarkupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEVELDESIGNERTOOLS_API ILevelMarkupInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FVector GetMarkupLocation() const = 0;
	virtual FTransform GetMarkupTransform() const = 0;
	virtual ELevelMarkupType GetLevelMarkupType() const = 0;
	virtual void UpdateFromMarkup(UObject* Object) const = 0;
};