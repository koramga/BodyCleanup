// Fill out your copyright notice in the Description page of Project Settings.


#include "CapabilitySystemComponent.h"
#include "CAPAffect.h"
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

	TArray<UCAPAffect*> DoneAffects;
	
	for(UCAPAffect* CAPAffect : OwnCAPAffects)
	{
		if(IsValid(CAPAffect))
		{
			CAPAffect->Tick(DeltaTime);

			if(CAPAffect->IsDone())
			{
				DoneAffects.Add(CAPAffect);
			}
		}
	}

	for(UCAPAffect* DoneCAPAffect : DoneAffects)
	{
		OwnCAPAffects.Remove(DoneCAPAffect);
	}

	for(UCAPAbility* CAPAbility : CAPAbilities)
	{
		CAPAbility->Tick(DeltaTime);
	}
}

bool UCapabilitySystemComponent::IsBlockEffect(UCAPEffect* CAPEffect)
{
	const FGameplayTagContainer& EffectAssetTag = CAPEffect->GetEffectAssetTags();
	
	for(UCAPAffect* CAPAffect : OwnCAPAffects)
	{
		TSoftObjectPtr<UCAPEffect> CAPEffectInAffect = CAPAffect->GetEffect();

		const FGameplayTagContainer& BlockAssetTags = CAPEffectInAffect->GetBlockAssetTags();

		if(BlockAssetTags.DoesTagContainerMatch(EffectAssetTag, EGameplayTagMatchType::IncludeParentTags, EGameplayTagMatchType::IncludeParentTags, EGameplayContainerMatchType::Any))
		{
			//UE_LOG(LogTemp, Display, TEXT("koramga Block"));
			return true;
		}
	}

	return false;
}

TSoftObjectPtr<UCAPAttributeSet> UCapabilitySystemComponent::AddAttribute(TSubclassOf<UCAPAttributeSet> CAPAttributeSetClass)
{
	TSoftObjectPtr<UCAPAttributeSet> CAPAttributeSet;

	UCAPAttributeSet* NewCAPAttributeSet = NewObject<UCAPAttributeSet>(this, CAPAttributeSetClass);

	if(IsValid(NewCAPAttributeSet))
	{
		CAPAttributeSets.Add(NewCAPAttributeSet);
		CAPAttributeSet = NewCAPAttributeSet;
	}
	
	return CAPAttributeSet;
}

bool UCapabilitySystemComponent::ApplyGameplayEffectToTarget(class UCAPEffect* CAPEffect, UCapabilitySystemComponent* Target, int32 AbilityLevel, const TArray<FCAPEffectAdvantage>* Advantages)
{
	//어떻게 데이터를 푸쉬해버릴까? 규칙을 어떻게 할까?
	if(IsBlockEffect(CAPEffect))
	{
		return false;
	}
	
	UCAPAffect* CAPAffect = NewObject<UCAPAffect>();

	if(IsValid(CAPAffect))
	{
		CAPAffect->SetSourceCapabilitySystemComponent(this);
		CAPAffect->SetTargetCapabilitySystemComponent(Target);
		CAPAffect->SetEffect(CAPEffect, AbilityLevel);
		if(nullptr != Advantages)
		{
			CAPAffect->SetAdvantage(*Advantages);
		}
		OwnCAPAffects.Add(CAPAffect);
	}

	return true;
}

bool UCapabilitySystemComponent::ApplyGameplayEffectToSelf(UCAPEffect* CAPEffect, int32 AbilityLevel,
	const TArray<FCAPEffectAdvantage>* Advantages)
{
	if(IsBlockEffect(CAPEffect))
	{
		return false;
	}
	
	UCAPAffect* CAPAffect = NewObject<UCAPAffect>();

	if(IsValid(CAPAffect))
	{
		CAPAffect->SetSourceCapabilitySystemComponent(this);
		CAPAffect->SetTargetCapabilitySystemComponent(this);
		CAPAffect->SetEffect(CAPEffect, AbilityLevel);
		if(nullptr != Advantages)
		{
			CAPAffect->SetAdvantage(*Advantages);
		}
		OwnCAPAffects.Add(CAPAffect);
	}

	return true;
}

bool UCapabilitySystemComponent::AffectFrom(TSoftObjectPtr<UCAPAffect> Affect, const FName& AttributeName, ECAPModifierOp ModifierOp, float Value)
{
	//누군가에게 영향을 받았다.

	for(UCAPAttributeSet* CAPAttribute : CAPAttributeSets)
	{
		if(CAPAttribute->AffectAttribute(Affect, AttributeName, ModifierOp, Value))
		{
			return true;
		}
	}
	
	return false;
}

void UCapabilitySystemComponent::AffectTo(TSoftObjectPtr<UCAPAffect> Affect)
{
	//누군가에게 영향을 줬다.
}

TSoftObjectPtr<UCAPAbility> UCapabilitySystemComponent::AddAbility(TSubclassOf<UCAPAbility> CAPAbilityClass, int32 AbilityLevel)
{	
	TSoftObjectPtr<UCAPAbility> CAPAbility;

	UCAPAbility* NewCAPAbility = NewObject<UCAPAbility>(this, CAPAbilityClass);

	if(IsValid(NewCAPAbility))
	{
		NewCAPAbility->Initialize(this);
		NewCAPAbility->SetAbilityLevel(AbilityLevel);
		CAPAbilities.Add(NewCAPAbility);		
		CAPAbility = NewCAPAbility;
	}
	
	return CAPAbility;
}

bool UCapabilitySystemComponent::TryActivateAbilityByClass(TSubclassOf<UCAPAbility> AbilityClass)
{
	for(UCAPAbility* CAPAbility : CAPAbilities)
	{
		if(CAPAbility->IsA(AbilityClass))
		{
			return CAPAbility->Activate();
		}
	}

	return false;
}

bool UCapabilitySystemComponent::TryActivateAbilityByTag(const FGameplayTag& Tag)
{
	for(UCAPAbility* CAPAbility : CAPAbilities)
	{
		if(CAPAbility->IsAbilityTag(Tag))
		{
			return CAPAbility->Activate();			
		}
	}

	return false;
}

bool UCapabilitySystemComponent::TryDeActivateAbilityByTag(const FGameplayTag& Tag)
{
	for(UCAPAbility* CAPAbility : CAPAbilities)
	{
		if(CAPAbility->IsAbilityTag(Tag))
		{
			return CAPAbility->DeActivate();			
		}
	}

	return false;
}

bool UCapabilitySystemComponent::CanActivateAbilityByTag(const FGameplayTag& Tag)
{
	for(UCAPAbility* CAPAbility : CAPAbilities)
	{
		if(CAPAbility->IsAbilityTag(Tag))
		{
			return CAPAbility->CanActivate();
		}
	}

	return false;
}

bool UCapabilitySystemComponent::IsActivateAbilityByTag(const FGameplayTag& Tag)
{
	for(UCAPAbility* CAPAbility : CAPAbilities)
	{
		if(CAPAbility->IsAbilityTag(Tag))
		{
			return CAPAbility->IsActivate();
		}
	}
	
	return false;
}
