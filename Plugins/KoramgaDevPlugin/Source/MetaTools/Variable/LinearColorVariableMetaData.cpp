// Fill out your copyright notice in the Description page of Project Settings.


#include "LinearColorVariableMetaData.h"

#include "MetaTools/Utility/MetaToolsFunctionLibrary.h"

FLinearColorVariableMetaData::FLinearColorVariableMetaData()
{
	MetaVariableType = EMetaVariableType::Vector;
}

TMetaVariable FLinearColorVariableMetaData::GetMetaVariable() const
{
	TMetaVariable MetaVariable;

	if (EMetaVariableScope::Normal == MetaVariableScope)
	{
		MetaVariable.Set<FLinearColor>(NormalVariableMetaData.Value);
	}
	else if(EMetaVariableScope::Range == MetaVariableScope)
	{
		TMetaVariable MinMetaVariable;
		TMetaVariable MaxMetaVariable;
		
		MinMetaVariable.Set<FLinearColor>(RangeVariableMetaData.Min);
		MaxMetaVariable.Set<FLinearColor>(RangeVariableMetaData.Max);

		MetaVariable = UMetaToolsFunctionLibrary::MakeRangeScopeVariable(MinMetaVariable, MaxMetaVariable);
	}

	return MetaVariable;
}