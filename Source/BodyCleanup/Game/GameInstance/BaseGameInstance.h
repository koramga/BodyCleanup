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
UCLASS()
class BODYCLEANUP_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable*	StatNameDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<EGameStatType, FName>	StatTypeNames;

public :
	virtual void Init() override;
	FName GetStatTypeToName(EGameStatType StatType);
};
