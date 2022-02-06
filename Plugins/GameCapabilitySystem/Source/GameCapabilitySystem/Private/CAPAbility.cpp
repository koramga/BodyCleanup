// Fill out your copyright notice in the Description page of Project Settings.


#include "CAPAbility.h"

#include "CapabilitySystemComponent.h"
#include "CAPEffect.h"

void UCAPAbility::OnActivateAbility()
{
	
}

void UCAPAbility::OnEndAbility()
{
	
}

void UCAPAbility::CommitAbility()
{
	if(OwnerCapabilitySystemComponent.IsValid())
	{
		if(IsValid(CostCAPEffect))
		{
			OwnerCapabilitySystemComponent->ApplyGameplayEffectToSelf(CostCAPEffect, AbilityLevel);
		}		
	}
}

void UCAPAbility::Initialize(TSoftObjectPtr<class UCapabilitySystemComponent> InOwnerCapabilitySystemComponent)
{
	OwnerCapabilitySystemComponent = InOwnerCapabilitySystemComponent;
	
	if(IsValid(CostCAPEffectClass))
	{
		CostCAPEffect = NewObject<UCAPEffect>(this, CostCAPEffectClass);
	}
}

bool UCAPAbility::IsActivate()
{
	return bIsActivate;
}

bool UCAPAbility::CanActivate()
{
	return true;
}

void UCAPAbility::Tick(float DeltaTime)
{
	
}

bool UCAPAbility::Activate()
{
	if(false == IsActivate()
		&& CanActivate())
	{
		CurrentCooldown = Cooldown;
		bIsActivate = true;
		OnActivateAbility();
		return true;
	}

	return false;
}

bool UCAPAbility::DeActivate()
{
	if(IsActivate())
	{
		bIsActivate = false;
		OnEndAbility();
		return true;
	}

	return false;
}

void UCAPAbility::SetAbilityLevel(int32 InAbilityLevel)
{
	AbilityLevel = InAbilityLevel;
}

int32 UCAPAbility::GetAbilityLevel() const
{
	return AbilityLevel;
}
