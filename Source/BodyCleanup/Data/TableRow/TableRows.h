// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ExDefines.h"
#include "Engine/DataTable.h"
#include "TableRows.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FGameStatNameTableRow
	: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EGameStatType	GameStatType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName			Name;
};
