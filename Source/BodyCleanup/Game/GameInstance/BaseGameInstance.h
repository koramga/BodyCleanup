// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ExDefines.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */

USTRUCT()
struct FLevelDescriptionDataAssetGroup
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<class ULevelDescriptionDataAsset*>	LevelDescriptionDataAssets;
};

UCLASS()
class BODYCLEANUP_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable*	StatNameDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* KeyboardControlDataTable;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class ULevelDescriptionDataAsset*>	LevelDescriptionDataAssets;

protected:
	UPROPERTY()
	TMap<EGameStatType, FName>	StatTypeNames;

	UPROPERTY()
	TMap<ELevelRoleType, FLevelDescriptionDataAssetGroup> LevelDescriptionDataAssetGroupMap;
	
public :
	virtual void Init() override;
	FName GetStatTypeToName(EGameStatType StatType);
	void GetKeyboardControlElements(TArray<struct FKeyboardControlTableRow>& KeyboardControlTableRows) const;
	const FLevelDescriptionDataAssetGroup* GetLevelDescriptionDataAssetGroup(ELevelRoleType LevelRoleType) const;
	void GetScripts(TArray<struct FScriptTableRow>& ScriptTableRows, const FName& InSceneName);
};
