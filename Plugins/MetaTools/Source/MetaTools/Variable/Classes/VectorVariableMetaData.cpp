// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorVariableMetaData.h"
#include "../../Utility/MetaToolsFunctionLibrary.h"

FVectorVariableMetaData::FVectorVariableMetaData()
{
	MetaVariableType = EMetaVariableType::Vector;
}

TMetaVariable FVectorVariableMetaData::GetMetaVariable() const
{
	TMetaVariable MetaVariable;

	if (EMetaVariableScope::Normal == MetaVariableScope)
	{
		MetaVariable.Set<FVector>(NormalVectorMetaData.Vector);
	}
	else if(EMetaVariableScope::Range == MetaVariableScope)
	{
		TMetaVariable MinMetaVariable;
		TMetaVariable MaxMetaVariable;
		
		MinMetaVariable.Set<FVector>(RangeVectorMetaData.Min);
		MaxMetaVariable.Set<FVector>(RangeVectorMetaData.Max);

		MetaVariable = UMetaToolsFunctionLibrary::MakeRangeScopeVariable(MinMetaVariable, MaxMetaVariable);
	}

	return MetaVariable;
}