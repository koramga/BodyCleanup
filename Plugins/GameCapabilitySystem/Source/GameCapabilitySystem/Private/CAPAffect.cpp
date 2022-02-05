// Fill out your copyright notice in the Description page of Project Settings.


#include "CAPAffect.h"
#include "CAPEffect.h"
#include "CapabilitySystemComponent.h"

UCAPAffect::UCAPAffect()
{
	bIsDone = false;
}

void UCAPAffect::__SetDone()
{
	bIsDone = true;
}

bool UCAPAffect::ProcessDone()
{
	if(false == CAPEffect.IsValid())
	{
		__SetDone();
		return false;
	}

	if(false == SourceCapabilitySystemComponent.IsValid())
	{
		__SetDone();
		return false;
	}

	if(false == TargetCapabilitySystemComponent.IsValid())
	{
		__SetDone();
		return false;
	}

	return true;
}

void UCAPAffect::SetEffect(UCAPEffect* InCAPEffect, int32 InAbilityLevel)
{
	CAPEffect = InCAPEffect;
	AbilityLevel = InAbilityLevel;
}

void UCAPAffect::SetSourceCapabilitySystemComponent(UCapabilitySystemComponent* InSourceCapabilitySystemComponent)
{
	SourceCapabilitySystemComponent = InSourceCapabilitySystemComponent;
}

void UCAPAffect::SetTargetCapabilitySystemComponent(UCapabilitySystemComponent* InTargetCapabilitySystemComponent)
{
	TargetCapabilitySystemComponent = InTargetCapabilitySystemComponent;
}

void UCAPAffect::BeginPlay()
{
	if(false == ProcessDone())
	{
		
	}
}

void UCAPAffect::Tick(float DeltaTime)
{
	if(false == ProcessDone())
	{
		return;
	}

	RemainTime -= DeltaTime;
	TotalTickTime += DeltaTime;
	
	if(RemainTime <= 0.f
		&& false == bIsFinish)
	{
		ECAPEffectDurationPolicy DurationPolicy =  CAPEffect->GetEffectDurationPolicy();

		const FCAPEffectModifierEvaluatedData* EffectModifierEvaluatedData = CAPEffect->GetEffectModifierEvaluatedData();

		FFloatVariableMetaData Magnitude = CAPEffect->GetMagnitude(AbilityLevel);
		float MagnitudeVariable = Magnitude.GetMetaVariable().Get<float>();
		
		if(TargetCapabilitySystemComponent->AffectFrom(EffectModifierEvaluatedData->AttributeName, EffectModifierEvaluatedData->ModifierOp, MagnitudeVariable))
		{
			SourceCapabilitySystemComponent->AffectTo();
		}
		
		if(ECAPEffectDurationPolicy::Instant == DurationPolicy)
		{
			__SetDone();
		}
		else if(ECAPEffectDurationPolicy::Duration == DurationPolicy)
		{
			if(TotalTickTime >= CAPEffect->GetEffectDurationMagnitude()->Duration)
			{
				__SetDone();
			}
			else
			{
				const FCAPEffectPeriodMagnitude* Period = CAPEffect->GetEffectPeriodMagnitude();
			}
		}

	}	
}

bool UCAPAffect::IsDone() const
{
	return bIsDone;
}