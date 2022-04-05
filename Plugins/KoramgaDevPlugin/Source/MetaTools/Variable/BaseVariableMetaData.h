// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseVariableMetaData.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EMetaVariableType : uint8
{
	Bool,
	Int,
	Float,
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

typedef TVariant<bool, int32, float, FVector, FVector4, FLinearColor> TMetaVariable;

USTRUCT(BlueprintType)
struct METATOOLS_API FBaseVariableMetaData
{
	GENERATED_BODY()

public :
	FBaseVariableMetaData();

protected:
	EMetaVariableType	MetaVariableType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMetaVariableScope	MetaVariableScope;

public:
	virtual EMetaVariableType GetMetaVariableType() const;
	virtual EMetaVariableScope GetMetaVariableScope() const;
	virtual TMetaVariable GetMetaVariable() const;
};
