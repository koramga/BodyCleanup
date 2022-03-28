// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorVariableMetaData.h"
#include "../Utility/MetaToolsFunctionLibrary.h"

FVectorVariableMetaData::FVectorVariableMetaData()
{
	MetaVariableType = EMetaVariableType::Vector;
}

TMetaVariable FVectorVariableMetaData::GetMetaVariable() const
{
	TMetaVariable MetaVariable;

	if (EMetaVariableScope::Normal == MetaVariableScope)
	{
		MetaVariable.Set<FVector>(NormalVariableMetaData.Value);
	}
	else if(EMetaVariableScope::Range == MetaVariableScope)
	{
		TMetaVariable MinMetaVariable;
		TMetaVariable MaxMetaVariable;
		
		MinMetaVariable.Set<FVector>(RangeVariableMetaData.Min);
		MaxMetaVariable.Set<FVector>(RangeVariableMetaData.Max);

		MetaVariable = UMetaToolsFunctionLibrary::MakeRangeScopeVariable(MinMetaVariable, MaxMetaVariable);
	}

	return MetaVariable;
}