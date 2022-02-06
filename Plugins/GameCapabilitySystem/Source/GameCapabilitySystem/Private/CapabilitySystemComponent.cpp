// Fill out your copyright notice in the Description page of Project Settings.


#include "CapabilitySystemComponent.h"

#include "CAPAffect.h"
#include "CAPAttributeSet.h"
#include "CAPEffect.h"
#include "CAPTypes.h"
#include "CAPAffect.h"

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

	const FGameplayTagContainer& EffectAssetTag = CAPEffect->GetEffectAssetTags();
	
	for(UCAPAffect* CAPAffect : OwnCAPAffects)
	{
		TSoftObjectPtr<UCAPEffect> CAPEffectInAffect = CAPAffect->GetEffect();

		const FGameplayTagContainer& BlockAssetTags = CAPEffectInAffect->GetBlockAssetTags();

		if(BlockAssetTags.DoesTagContainerMatch(EffectAssetTag, EGameplayTagMatchType::IncludeParentTags, EGameplayTagMatchType::IncludeParentTags, EGameplayContainerMatchType::Any))
		{
			//UE_LOG(LogTemp, Display, TEXT("koramga Block"));
			return false;
		}
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