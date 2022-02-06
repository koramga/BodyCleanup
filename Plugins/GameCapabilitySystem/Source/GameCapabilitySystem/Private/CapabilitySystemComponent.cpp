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

void UCapabilitySystemComponent::ApplyGameplayEffectToTarget(UCAPEffect* CAPEffect, UCapabilitySystemComponent* Target, int32 Ability)
{
	//어떻게 데이터를 푸쉬해버릴까? 규칙을 어떻게 할까?
	UCAPAffect* CAPAffect = NewObject<UCAPAffect>();

	if(IsValid(CAPAffect))
	{
		CAPAffect->SetSourceCapabilitySystemComponent(this);
		CAPAffect->SetTargetCapabilitySystemComponent(Target);
		CAPAffect->SetEffect(CAPEffect, Ability);
		OwnCAPAffects.Add(CAPAffect);
	}
}

bool UCapabilitySystemComponent::AffectFrom(const FName& AttributeName, ECAPModifierOp ModifierOp, float Value)
{
	//누군가에게 영향을 받았다.

	for(UCAPAttributeSet* CAPAttribute : CAPAttributeSets)
	{
		if(CAPAttribute->AffectAttribute(AttributeName, ModifierOp, Value))
		{
			return true;
		}
	}
	
	return false;
}

void UCapabilitySystemComponent::AffectTo()
{
	//누군가에게 영향을 줬다.
}