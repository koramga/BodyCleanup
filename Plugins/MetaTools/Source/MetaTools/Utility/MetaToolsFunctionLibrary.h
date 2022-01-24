// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../Variable/Interface/VariableMetaDataInterface.h"
#include "MetaToolsFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class METATOOLS_API UMetaToolsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public :
	static TMetaVariable MakeRangeScopeVariable(const TMetaVariable& LMetaVariant, const TMetaVariable& RMetaVariant);

};
