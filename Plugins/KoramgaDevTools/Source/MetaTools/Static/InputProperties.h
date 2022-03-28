// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputProperties.generated.h"

/**
 * 
*/

USTRUCT(BlueprintType)
struct METATOOLS_API FPropertyName
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool			bIsTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName>	Names;
};
