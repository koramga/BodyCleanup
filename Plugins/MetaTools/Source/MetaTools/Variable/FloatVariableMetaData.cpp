// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatVariableMetaData.h"
#include "../Utility/MetaToolsFunctionLibrary.h"

FFloatVariableMetaData::FFloatVariableMetaData()
{
	MetaVariableType = EMetaVariableType::Float;
}

TMetaVariable FFloatVariableMetaData::GetMetaVariable() const
{
	TMetaVariable MetaVariable;

	if (EMetaVariableScope::Normal == MetaVariableScope)
	{
		MetaVariable.Set<float>(NormalVariableMetaData.Value);
	}
	else if (EMetaVariableScope::Range == MetaVariableScope)
	{
		TMetaVariable MinMetaVariable;
		TMetaVariable MaxMetaVariable;

		MinMetaVariable.Set<float>(RangeVariableMetaData.Min);
		MaxMetaVariable.Set<float>(RangeVariableMetaData.Max);

		MetaVariable = UMetaToolsFunctionLibrary::MakeRangeScopeVariable(MinMetaVariable, MaxMetaVariable);
	}

	return MetaVariable;
}