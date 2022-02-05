// Fill out your copyright notice in the Description page of Project Settings.


#include "CapabilitySystemComponent.h"
#include "CAPAttributeSet.h"
#include "CAPEffect.h"
#include "CAPTypes.h"

// Sets default values for this component's properties
UCapabilitySystemComponent::UCapabilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCapabilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCapabilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TSoftObjectPtr<UCAPAttributeSet> UCapabilitySystemComponent::AddAttribute(TSubclassOf<UCAPAttributeSet> CAPAttributeSetClass)
{
	TSoftObjectPtr<UCAPAttributeSet> CAPAttributeSet;

	if(CAPAttributeSet.IsValid())
	{
		UCAPAttributeSet* NewCAPAttributeSet = NewObject<UCAPAttributeSet>(this, CAPAttributeSetClass);

		if(IsValid(NewCAPAttributeSet))
		{
			CAPAttributeSets.Add(NewCAPAttributeSet);
			CAPAttributeSet = NewCAPAttributeSet;
		}
	}	 
	
	return CAPAttributeSet;
}

void UCapabilitySystemComponent::ApplyGameplayEffectToTarget(UCAPEffect* CAPEffect, UCapabilitySystemComponent* Target)
{
}

