// Fill out your copyright notice in the Description page of Project Settings.


#include "CAPEffect.h"

ECAPEffectDurationPolicy UCAPEffect::GetEffectDurationPolicy() const
{
	return DurationPolicy;
}

const FCAPEffectDurationMagnitude* UCAPEffect::GetEffectDurationMagnitude() const
{
	return &Duration;
}

const FCAPEffectPeriodMagnitude* UCAPEffect::GetEffectPeriodMagnitude() const
{
	return &Period;
}

const FCAPEffectModifierEvaluatedData* UCAPEffect::GetEffectModifierEvaluatedData() const
{
	return &Modifiers;
}

FFloatVariableMetaData UCAPEffect::GetMagnitude(int AbilityLevel)
{
	FFloatVariableMetaData Magnitude = Modifiers.Magnitude;
	
	if(ECAPEffectMagnitudeType::AbilityLevel == Modifiers.MagnitudeType)
	{
		for(const FCAPEffectModifierMagnitude& CAPEffectModifierMagnitde : Magnitudes)
		{
			if(CAPEffectModifierMagnitde.AbilityLevel == AbilityLevel)
			{
				Magnitude = CAPEffectModifierMagnitde.Magnitude;
			}
		}
	}

	return Magnitude;
}
