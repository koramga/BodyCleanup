// Fill out your copyright notice in the Description page of Project Settings.


#include "IntegerVariableMetaData.h"

#include "MetaTools/Utility/MetaToolsFunctionLibrary.h"

FIntegerVariableMetaData::FIntegerVariableMetaData()
{
	MetaVariableType = EMetaVariableType::Int;
}

TMetaVariable FIntegerVariableMetaData::GetMetaVariable() const
{
	TMetaVariable MetaVariable;

	if (EMetaVariableScope::Normal == MetaVariableScope)
	{
		MetaVariable.Set<int>(NormalVariableMetaData.Value);
	}
	else if(EMetaVariableScope::Range == MetaVariableScope)
	{
		TMetaVariable MinMetaVariable;
		TMetaVariable MaxMetaVariable;
		
		MinMetaVariable.Set<int>(RangeVariableMetaData.Min);
		MaxMetaVariable.Set<int>(RangeVariableMetaData.Max);

		MetaVariable = UMetaToolsFunctionLibrary::MakeRangeScopeVariable(MinMetaVariable, MaxMetaVariable);
	}

	return MetaVariable;
}
