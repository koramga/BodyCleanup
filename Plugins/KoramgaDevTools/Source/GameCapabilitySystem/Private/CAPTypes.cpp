// Fill out your copyright notice in the Description page of Project Settings.


#include "CAPTypes.h"

const FCAPEffectWeightMagnitude& FCAPEffectModifierEvaluatedData::GetWeightMagnitude(int32 AbilityLevel) const
{
	if(ECAPEffectMagnitudeType::AbilityLevel == MagnitudeType)
	{
		if(AbilityLevelMagnitudes.Num() > AbilityLevel)
		{
			return AbilityLevelMagnitudes[AbilityLevel];
		}
	}

	return DefaultMagnitude;
}