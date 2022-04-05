// Fill out your copyright notice in the Description page of Project Settings.


#include "Vector4VariableMetaData.h"

#include "MetaTools/Utility/MetaToolsFunctionLibrary.h"

FVector4VariableMetaData::FVector4VariableMetaData()
{
	MetaVariableType = EMetaVariableType::Vector4;
}

TMetaVariable FVector4VariableMetaData::GetMetaVariable() const
{
	TMetaVariable MetaVariable;

	if (EMetaVariableScope::Normal == MetaVariableScope)
	{
		MetaVariable.Set<FVector4>(NormalVariableMetaData.Value);
	}
	else if(EMetaVariableScope::Range == MetaVariableScope)
	{
		TMetaVariable MinMetaVariable;
		TMetaVariable MaxMetaVariable;
		
		MinMetaVariable.Set<FVector4>(RangeVariableMetaData.Min);
		MaxMetaVariable.Set<FVector4>(RangeVariableMetaData.Max);

		MetaVariable = UMetaToolsFunctionLibrary::MakeRangeScopeVariable(MinMetaVariable, MaxMetaVariable);
	}

	return MetaVariable;
}