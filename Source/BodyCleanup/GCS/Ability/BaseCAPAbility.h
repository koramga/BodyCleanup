// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CAPAbility.h"
#include "../../ExDefines.h"
#include "BaseCAPAbility.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UBaseCAPAbility : public UCAPAbility
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AbilityRange;

public :
	virtual void LeftAnimationType(EAnimationType InAnimationType);
	float GetAbilityRange() const;
};
