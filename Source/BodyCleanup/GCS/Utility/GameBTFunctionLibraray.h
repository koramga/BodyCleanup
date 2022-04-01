// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/BTControllerInterface.h"
#include "UObject/Object.h"
#include "GameBTFunctionLibraray.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UGameBTFunctionLibraray : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public :
	static ETeamType GetTeamType(AActor* Actor);
	static bool IsEnemy(ETeamType LTeamType, ETeamType RTeamType);
	static bool IsEnemy(AActor* LActor, AActor* RActor);	
};
