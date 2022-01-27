// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected :
    //Attributes for Health
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttribute")
    FGameplayAttributeData  Health;
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Health);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttribute")
    FGameplayAttributeData  MaxHealth;
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxHealth);
	
};
