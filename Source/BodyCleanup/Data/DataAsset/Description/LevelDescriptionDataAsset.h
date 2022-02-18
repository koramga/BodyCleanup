// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDescriptionDataAsset.h"
#include "LevelDescriptionDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ULevelDescriptionDataAsset : public UBaseDescriptionDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ELevelRoleType		LevelRoleType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName				UELevelName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName				LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString				Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UDataTable*	ScriptDataTable;

public :
	ELevelRoleType GetLevelRoleType() const;
	FName GetUELevelName() const;
	FName GetLevelName() const;
	class UDataTable* GetScriptDataTable() const;
};