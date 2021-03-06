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
	
	for(UCAPAffect* CAPAffect : WorkCAPAffects)
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
		WorkCAPAffects.Remove(DoneCAPAffect);
	}

	for(UCAPAbility* CAPAbility : CAPAbilities)
	{
		CAPAbility->Tick(DeltaTime);
	}
}

bool UCapabilitySystemComponent::IsBlockEffect(TSoftObjectPtr<UCAPEffect> CAPEffect)
{
	const FGameplayTagContainer& EffectAssetTag = CAPEffect->GetEffectAssetTags();

	if(BlockGameplayTagContainer.DoesTagContainerMatch(EffectAssetTag, EGameplayTagMatchType::IncludeParentTags, EGameplayTagMatchType::IncludeParentTags, EGameplayContainerMatchType::Any))
	{
		//UE_LOG(LogTemp, Display, TEXT("koramga Block"));
		return true;
	}
	
	for(UCAPAffect* CAPAffect : WorkCAPAffects)
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

FCAPAttributeData* UCapabilitySystemComponent::GetAttributeDataByAttributeName(const FName& AttributeName)
{
	for(UCAPAttributeSet* AttributeSet : CAPAttributeSets)
	{
		FCAPAttributeData* CAPAttributeData = AttributeSet->GetAttributeDataByName(AttributeName);

		if(nullptr != CAPAttributeData)
		{
			return CAPAttributeData;
		}
	}

	return nullptr;
}

bool UCapabilitySystemComponent::ApplyGameplayEffectToTarget(TSoftObjectPtr<UCAPEffect> CAPEffect, UCapabilitySystemComponent* Target, int32 AbilityLevel, float Weight,  const FHitResult& HitResult, const TArray<FCAPEffectAdvantage>* Advantages)
{
	//????????? ???????????? ??????????????????? ????????? ????????? ???????
	if(Target->IsBlockEffect(CAPEffect))
	{
		return false;
	}
	
	UCAPAffect* CAPAffect = NewObject<UCAPAffect>();

	if(IsValid(CAPAffect))
	{
		CAPAffect->SetSourceCapabilitySystemComponent(this);
		CAPAffect->SetTargetCapabilitySystemComponent(Target);
		CAPAffect->SetEffect(CAPEffect, AbilityLevel, Weight);
		CAPAffect->SetHitResult(HitResult);
		if(nullptr != Advantages)
		{
			CAPAffect->SetAdvantage(*Advantages);
		}
		WorkCAPAffects.Add(CAPAffect);
	}

	return true;
}

bool UCapabilitySystemComponent::ApplyGameplayEffectFromSource(TSoftObjectPtr<UCAPEffect> CAPEffect,
	UCapabilitySystemComponent* Source, int32 AbilityLevel, float Weight, const FHitResult& HitResult, const TArray<FCAPEffectAdvantage>* Advantages)
{
	//????????? ???????????? ??????????????????? ????????? ????????? ???????
	if(Source->IsBlockEffect(CAPEffect))
	{
		return false;
	}
	
	UCAPAffect* CAPAffect = NewObject<UCAPAffect>();

	if(IsValid(CAPAffect))
	{
		CAPAffect->SetSourceCapabilitySystemComponent(Source);
		CAPAffect->SetTargetCapabilitySystemComponent(this);
		CAPAffect->SetEffect(CAPEffect, AbilityLevel, Weight);
		CAPAffect->SetHitResult(HitResult);
		if(nullptr != Advantages)
		{
			CAPAffect->SetAdvantage(*Advantages);
		}
		WorkCAPAffects.Add(CAPAffect);
	}

	return true;
}

bool UCapabilitySystemComponent::ApplyGameplayEffectToSelf(TSoftObjectPtr<UCAPEffect> CAPEffect, int32 AbilityLevel,
	const FHitResult& HitResult, const TArray<FCAPEffectAdvantage>* Advantages)
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
		CAPAffect->SetHitResult(HitResult);
		if(nullptr != Advantages)
		{
			CAPAffect->SetAdvantage(*Advantages);
		}
		WorkCAPAffects.Add(CAPAffect);
	}

	return true;
}

bool UCapabilitySystemComponent::AffectFrom(TSoftObjectPtr<UCAPAffect> Affect, const FName& AttributeName, ECAPModifierOp ModifierOp, float Value, const FHitResult& HitResult)
{
	//??????????????? ????????? ?????????.

	for(UCAPAttributeSet* CAPAttribute : CAPAttributeSets)
	{
		if(CAPAttribute->AffectAttribute(Affect, AttributeName, ModifierOp, Value, HitResult))
		{
			return true;
		}
	}
	
	return false;
}

void UCapabilitySystemComponent::AddBlockGameplayTag(const FGameplayTag& GameplayTag)
{
	BlockGameplayTagContainer.AddTag(GameplayTag);
}

void UCapabilitySystemComponent::RemoveBlockGameplayTag(const FGameplayTag& GameplayTag)
{
	BlockGameplayTagContainer.RemoveTag(GameplayTag);
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

TSoftObjectPtr<UCAPAbility> UCapabilitySystemComponent::GetAbility(TSubclassOf<UCAPAbility> CAPAbilityClass) const
{
	for(UCAPAbility* CAPAbility : CAPAbilities)
	{
		if(CAPAbility->IsA(CAPAbilityClass))
		{
			return CAPAbility;
		}
	}

	return nullptr;	
}

TSoftObjectPtr<UCAPAbility> UCapabilitySystemComponent::GetAbilityFromIndex(int32 Index)
{
	if(CAPAbilities.Num() > Index)
	{
		return CAPAbilities[Index];
	}

	return nullptr;
}

TSoftObjectPtr<UCAPAbility> UCapabilitySystemComponent::GetActivateAbility() const
{
	for(UCAPAbility* CAPAbility : CAPAbilities)
	{
		if(CAPAbility->IsActivate())
		{
			return CAPAbility;
		}
	}

	return nullptr;
}

bool UCapabilitySystemComponent::RemoveAbility(TSubclassOf<UCAPAbility> CAPAbilityClass)
{
	for(UCAPAbility* CAPAbility : CAPAbilities)
	{
		if(CAPAbility->IsA(CAPAbilityClass))
		{
			if(CAPAbilities.Remove(CAPAbility) != INDEX_NONE)
			{
				return true;
			}

			return false;
		}
	}

	return false;
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

bool UCapabilitySystemComponent::IsActivateAbilityByClass(const TSubclassOf<UCAPAbility>& Class)
{
	for(UCAPAbility* CAPAbility : CAPAbilities)
	{
		if(CAPAbility->IsA(Class))
		{
			return CAPAbility->IsActivate();
		}
	}
	
	return false;	
}
