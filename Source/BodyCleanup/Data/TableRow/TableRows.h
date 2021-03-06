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

USTRUCT()
struct FKeyboardControlTableRow
	: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EKeyboardControlType	Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString					Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString					ImagePath;
};

USTRUCT()
struct FScriptTableRow
	: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName					SceneName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName					ActorName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString					Script;
};