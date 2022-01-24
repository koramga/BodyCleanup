// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interface/VariableMetaDataInterface.h"
#include "UObject/NoExportTypes.h"
#include "BaseVariableMetaData.generated.h"

/**
 * 
 */
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
