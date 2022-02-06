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

void UCAPAffect::SetAdvantage(const TArray<FCAPEffectAdvantage>& InAdvantages)
{
	Advantages = InAdvantages;
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
		const TArray<FCAPEffectModifierEvaluatedData>& Magnitudes = CAPEffect->GetModifierMagnitude();

		for(const FCAPEffectModifierEvaluatedData& Magnitude : Magnitudes)
		{
			FFloatVariableMetaData MagnitudeMetaData = Magnitude.GetMagnitude(AbilityLevel);
			float MagnitudeVariable = MagnitudeMetaData.GetMetaVariable().Get<float>();

			for(const FCAPEffectAdvantage& Advantage : Advantages)
			{
				if(Advantage.PropertyName == Magnitude.AttributeName)
				{
					MagnitudeVariable *= Advantage.Advantage;
					break;
				}
			}

			if(TargetCapabilitySystemComponent->AffectFrom(this, Magnitude.AttributeName, Magnitude.ModifierOp, MagnitudeVariable))
			{
				SourceCapabilitySystemComponent->AffectTo(this);
			}
		}
	}	
	ECAPEffectDurationPolicy DurationPolicy =  CAPEffect->GetEffectDurationPolicy();
	
	if(ECAPEffectDurationPolicy::Instant == DurationPolicy)
	{
		__SetDone();
	}
	else if(ECAPEffectDurationPolicy::Duration == DurationPolicy)
	{
		const FCAPEffectDurationMagnitude* DurationMagnitude = CAPEffect->GetEffectDurationMagnitude();
		const FCAPEffectPeriodMagnitude* PeriodMagnnitude = CAPEffect->GetEffectPeriodMagnitude();

		if(false == PeriodMagnnitude->ExecutePeriodicEffectOnApplication)
		{
			bIsFinish = true;
		}
		else
		{
			RemainTime = PeriodMagnnitude->Period;
		}

		if(TotalTickTime >= DurationMagnitude->Duration)
		{
			__SetDone();
		}
	}
	else if(ECAPEffectDurationPolicy::Infinite == DurationPolicy)
	{
		const FCAPEffectPeriodMagnitude* PeriodMagnnitude = CAPEffect->GetEffectPeriodMagnitude();

		if(false == PeriodMagnnitude->ExecutePeriodicEffectOnApplication)
		{
			bIsFinish = true;
		}
		else
		{
			RemainTime = PeriodMagnnitude->Period;
		}
	}
}

bool UCAPAffect::IsDone() const
{
	return bIsDone;
}

const TSoftObjectPtr<UCAPEffect> UCAPAffect::GetEffect() const
{
	return CAPEffect;
}
