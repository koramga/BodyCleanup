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

TSoftObjectPtr<UCapabilitySystemComponent> UCAPAbility::GetOwnerCapabilitySystemComponent() const
{
	return OwnerCapabilitySystemComponent;
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

	CurrentCooldown = InitCooldown;
}

bool UCAPAbility::IsActivate()
{
	return bIsActivate;
}

bool UCAPAbility::CanActivate()
{
	if(CurrentCooldown > 0.f)
	{
		return false;
	}
	
	return true;
}

void UCAPAbility::Tick(float DeltaTime)
{
	if(CurrentCooldown > 0.f)
	{
		CurrentCooldown -= DeltaTime;

		if(CurrentCooldown <= 0.f)
		{
			CurrentCooldown = 0.f;
		}		
	}	
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

bool UCAPAbility::IsAbilityTag(const FGameplayTag& GameplayTag)
{
	return AbilityTags.HasTagExact(GameplayTag);
}
