// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVariableMetaData.h"

EMetaVariableType UBaseVariableMetaData::GetMetaVariableType() const
{
	return MetaVariableType;
}

EMetaVariableScope UBaseVariableMetaData::GetMetaVariableScope() const
{
	return MetaVariableScope;
}

TMetaVariable UBaseVariableMetaData::GetMetaVariable() const
{
	TMetaVariable MetaVariable;

	MetaVariable.Set<int>(0);

	return MetaVariable;
}
