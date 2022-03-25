// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "GameGCSFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UGameGCSFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public :
	static const FGameplayTag GeneralAttackGameplayTag;
	static const FGameplayTag ChargingAttackGameplayTag;
	static const FGameplayTag SpecialAttackGameplayTag;
	static const FGameplayTag PlayerAttackGameplayTag;
};
