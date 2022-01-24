// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "VariableMetaDataInterface.generated.h"

UENUM(BlueprintType)
enum class EVariableType : uint8
{
	Vector,
	Vector4,
	Color,
	Float,
	Int,
	Bool,
};

UENUM(BlueprintType)
enum class EVariableMetaDataType : uint8
{
	Normal,
	Range,
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UVariableMetaDataInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class METATOOLS_API IVariableMetaDataInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
