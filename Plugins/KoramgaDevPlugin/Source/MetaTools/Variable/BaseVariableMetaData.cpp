// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVariableMetaData.h"

FBaseVariableMetaData::FBaseVariableMetaData()
{
	MetaVariableType = EMetaVariableType::Bool;
	MetaVariableScope = EMetaVariableScope::Normal;
}

EMetaVariableType FBaseVariableMetaData::GetMetaVariableType() const
{
	return MetaVariableType;
}

EMetaVariableScope FBaseVariableMetaData::GetMetaVariableScope() const
{
	return MetaVariableScope;
}

TMetaVariable FBaseVariableMetaData::GetMetaVariable() const
{
	return TMetaVariable();
}
