// Fill out your copyright notice in the Description page of Project Settings.


#include "CAPTypes.h"

FFloatVariableMetaData FCAPEffectModifierEvaluatedData::GetMagnitude(int32 AbilityLevel) const
{
	FFloatVariableMetaData Magnitude = DefaultMagnitude;

	if(ECAPEffectMagnitudeType::AbilityLevel == MagnitudeType)
	{
		if(AbilityLevelMagnitudes.Num() > AbilityLevel)
		{
			Magnitude = AbilityLevelMagnitudes[AbilityLevel];
		}
	}

	return Magnitude;
}