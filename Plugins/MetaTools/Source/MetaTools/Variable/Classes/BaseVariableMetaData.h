// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interface/VariableMetaDataInterface.h"
#include "UObject/NoExportTypes.h"
#include "BaseVariableMetaData.generated.h"

/**
 * 
 */
UCLASS()
class METATOOLS_API UBaseVariableMetaData : public UObject, public IVariableMetaDataInterface
{
	GENERATED_BODY()

protected:
	EMetaVariableType	MetaVariableType;
	EMetaVariableScope	MetaVariableScope;

public:
	virtual EMetaVariableType GetMetaVariableType() const override;
	virtual EMetaVariableScope GetMetaVariableScope() const override;
	virtual TMetaVariable GetMetaVariable() const override;
};
