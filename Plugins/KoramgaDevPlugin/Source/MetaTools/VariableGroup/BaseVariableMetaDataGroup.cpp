// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVariableMetaDataGroup.h"

FBaseVariableMetaDataGroup::FBaseVariableMetaDataGroup()
{
	
}

TMetaVariable FBaseVariableMetaDataGroup::GetMetaVariable() const
{
	switch (MetaVariableType)
	{
	case EMetaVariableType::Bool :
		return BoolVariableMetaData.GetMetaVariable();
	case EMetaVariableType::Float :
		return FloatVariableMetaData.GetMetaVariable();
	case EMetaVariableType::Int :
		return IntVariableMetaData.GetMetaVariable();
	case EMetaVariableType::Vector :
		return VectorVariableMetaData.GetMetaVariable();
	case EMetaVariableType::Vector4 :
		return Vector4VariableMetaData.GetMetaVariable();
	case EMetaVariableType::LinearColor :
		return LinearColorVariableMetaData.GetMetaVariable();
	}

	return TMetaVariable();
}

EMetaVariableType FBaseVariableMetaDataGroup::GetMetaVariableType() const
{
	return MetaVariableType;
}
