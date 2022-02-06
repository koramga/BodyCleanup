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


const TArray<FCAPEffectModifierEvaluatedData>& UCAPEffect::GetModifierMagnitude() const
{
	return Modifiers;
}
