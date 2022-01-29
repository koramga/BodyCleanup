// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAttributeSet.h"
#include "BaseStatsAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UBaseStatsAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

protected :
        //Attributes for Health
    UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName = "Health")
    float   __Health__;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName = "MaxHealth")
    float   __MaxHealth__;

    UPROPERTY(BlueprintReadOnly)
    FGameplayAttributeData  Health;

    UPROPERTY(BlueprintReadOnly)
    FGameplayAttributeData  MaxHealth;

protected :
    virtual void PostInitProperties() override;

public :
    ATTRIBUTE_ACCESSORS(UBaseStatsAttributeSet, Health);
    ATTRIBUTE_ACCESSORS(UBaseStatsAttributeSet, MaxHealth)
};
