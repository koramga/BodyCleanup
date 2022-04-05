// Fill out your copyright notice in the Description page of Project Settings.


#include "BoolVariableMetaData.h"

#include "MetaTools/Utility/MetaToolsFunctionLibrary.h"

FBooleanVariableMetaData::FBooleanVariableMetaData()
{
	MetaVariableType = EMetaVariableType::Bool;
}

TMetaVariable FBooleanVariableMetaData::GetMetaVariable() const
{
	TMetaVariable MetaVariable;

	if (EMetaVariableScope::Normal == MetaVariableScope)
	{
		MetaVariable.Set<bool>(NormalVariableMetaData.Value);
	}
	else if (EMetaVariableScope::Range == MetaVariableScope)
	{
		TMetaVariable MinMetaVariable;
		TMetaVariable MaxMetaVariable;

		MinMetaVariable.Set<bool>(RangeVariableMetaData.Min);
		MaxMetaVariable.Set<bool>(RangeVariableMetaData.Max);

		MetaVariable = UMetaToolsFunctionLibrary::MakeRangeScopeVariable(MinMetaVariable, MaxMetaVariable);
	}

	return MetaVariable;
}
