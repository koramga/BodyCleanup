// Fill out your copyright notice in the Description page of Project Settings.


#include "CAPAbility.h"

#include "CapabilitySystemComponent.h"
#include "CAPEffect.h"

void UCAPAbility::OnActivateAbility()
{
	Weight = 0.f;
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
		if(CostCAPEffect.IsValid())
		{
			OwnerCapabilitySystemComponent->ApplyGameplayEffectToSelf(CostCAPEffect, AbilityLevel);
		}		
	}
}

void UCAPAbility::AffectAbility(UCapabilitySystemComponent* Target, const FHitResult& HitResult)
{
	if(OwnerCapabilitySystemComponent.IsValid())
	{
		if(AbilityCAPEffect.IsValid())
		{
			//UE_LOG(LogTemp, Display, TEXT("AffectAbility Weight : <%.2f>"), Weight);
			
			OwnerCapabilitySystemComponent->ApplyGameplayEffectToTarget(AbilityCAPEffect, Target, AbilityLevel, Weight, HitResult);
		}
	}
}

void UCAPAbility::AffectAbilityFromSource(UCapabilitySystemComponent* Source, const FHitResult& HitResult)
{
	if(OwnerCapabilitySystemComponent.IsValid())
	{
		if(AbilityCAPEffect.IsValid())
		{
			//UE_LOG(LogTemp, Display, TEXT("AffectAbility Weight : <%.2f>"), Weight);
			
			OwnerCapabilitySystemComponent->ApplyGameplayEffectFromSource(AbilityCAPEffect, Source, AbilityLevel, Weight, HitResult);
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

	if(IsValid(AbilityCAPEffectClass))
	{
		AbilityCAPEffect = NewObject<UCAPEffect>(this, AbilityCAPEffectClass);
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

TSoftObjectPtr<UCAPEffect> UCAPAbility::GetAbilityCAPEffect() const
{
	return AbilityCAPEffect;
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

void UCAPAbility::SetWeight(float InWeight)
{
	Weight = InWeight;
}

void UCAPAbility::AddWeight(float InAddWeight)
{
	Weight += InAddWeight;
}

int32 UCAPAbility::GetAbilityLevel() const
{
	return AbilityLevel;
}

float UCAPAbility::GetWeight() const
{
	return Weight;
}

bool UCAPAbility::IsAbilityTag(const FGameplayTag& GameplayTag) const
{
	return AbilityTags.HasTagExact(GameplayTag);
}
