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
    float   SetupHealth;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName = "MaxHealth")
    float   SetupMaxHealth;

    UPROPERTY(BlueprintReadOnly)
    FGameplayAttributeData  Health;
    ATTRIBUTE_ACCESSORS(UBaseStatsAttributeSet, Health);

    UPROPERTY(BlueprintReadOnly)
    FGameplayAttributeData  MaxHealth;
    ATTRIBUTE_ACCESSORS(UBaseStatsAttributeSet, MaxHealth);

protected :
    virtual void PostInitProperties() override;
};
