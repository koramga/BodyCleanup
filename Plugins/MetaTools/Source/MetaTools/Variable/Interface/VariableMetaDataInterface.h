// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "VariableMetaDataInterface.generated.h"

UENUM(BlueprintType)
enum class EMetaVariableType : uint8
{
	Bool,
	Int,
	Float,
	Double,
	Vector,
	Vector4,
	LinearColor,
};

UENUM(BlueprintType)
enum class EMetaVariableScope : uint8
{
	Normal,
	Range,
};

typedef TVariant<bool, int32, float, double, FVector, FVector4, FLinearColor> TMetaVariable;

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
	virtual EMetaVariableType GetMetaVariableType() const = 0;
	virtual EMetaVariableScope GetMetaVariableScope() const = 0;
	virtual TMetaVariable GetMetaVariable() const = 0;
};
