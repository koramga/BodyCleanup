// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialInstanceVariable.h"

bool FMaterialInstanceVariable::SetMaterialInstanceParameter(UPrimitiveComponent* PrimitiveComponent) const
{
	UMaterialInstanceDynamic* MaterialInstanceDynamic = PrimitiveComponent->CreateDynamicMaterialInstance(DynamicMaterialInstanceElementIndex);

	if(IsValid(MaterialInstanceDynamic))
	{
		return SetMaterialInstanceParameter(MaterialInstanceDynamic);
	}

	return false;
}

bool FMaterialInstanceVariable::SetMaterialInstanceParameter(UPrimitiveComponent* PrimitiveComponent,
	const TMetaVariable& MetaVariable) const
{
	UMaterialInstanceDynamic* MaterialInstanceDynamic = PrimitiveComponent->CreateDynamicMaterialInstance(DynamicMaterialInstanceElementIndex);

	if(IsValid(MaterialInstanceDynamic))
	{
		return SetMaterialInstanceParameter(MaterialInstanceDynamic, MetaVariable);
	}

	return false;
}

bool FMaterialInstanceVariable::SetMaterialInstanceParameter(UMaterialInstanceDynamic* MaterialInstanceDynamic) const
{
	TMetaVariable MetaVariable = BaseVariableMetaDataGroup.GetMetaVariable();
	
	return SetMaterialInstanceParameter(MaterialInstanceDynamic, MetaVariable);

	/*
	if(IsValid(MaterialInstanceDynamic))
	{
		TMetaVariable MetaVariable = BaseVariableMetaDataGroup.GetMetaVariable();
		EMetaVariableType MetaVariableType = BaseVariableMetaDataGroup.GetMetaVariableType();

		switch (MetaVariableType)
		{
		case EMetaVariableType::Bool:
			MaterialInstanceDynamic->SetScalarParameterValue(ParameterName, MetaVariable.Get<bool>());
			break;

		case EMetaVariableType::Float :
			MaterialInstanceDynamic->SetScalarParameterValue(ParameterName, MetaVariable.Get<float>());
			break;

		case EMetaVariableType::Int :
			MaterialInstanceDynamic->SetScalarParameterValue(ParameterName, MetaVariable.Get<int>());
			break;

		case EMetaVariableType::Vector :
			MaterialInstanceDynamic->SetVectorParameterValue(ParameterName, MetaVariable.Get<FVector>());
			break;

		case EMetaVariableType::Vector4 :
			{
				FVector4 Vector4  = MetaVariable.Get<FVector4>();
				FLinearColor LinearColor;
				LinearColor.R = Vector4.X;
				LinearColor.G = Vector4.Y;
				LinearColor.B = Vector4.Z;
				LinearColor.A = Vector4.W;

				MaterialInstanceDynamic->SetVectorParameterValue(ParameterName, LinearColor);
			}
			break;

		case EMetaVariableType::LinearColor :
			MaterialInstanceDynamic->SetVectorParameterValue(ParameterName, MetaVariable.Get<FLinearColor>());
			break;
		}

		return true;
	}
	
	return false;
	*/	
}

bool FMaterialInstanceVariable::SetMaterialInstanceParameter(UMaterialInstanceDynamic* MaterialInstanceDynamic,
	const TMetaVariable& MetaVariable) const
{
	if(IsValid(MaterialInstanceDynamic))
	{
		EMetaVariableType MetaVariableType = static_cast<EMetaVariableType>(MetaVariable.GetIndex());

		switch (MetaVariableType)
		{
		case EMetaVariableType::Bool:
			MaterialInstanceDynamic->SetScalarParameterValue(ParameterName, MetaVariable.Get<bool>());
			break;

		case EMetaVariableType::Float :
			MaterialInstanceDynamic->SetScalarParameterValue(ParameterName, MetaVariable.Get<float>());
			break;

		case EMetaVariableType::Int :
			MaterialInstanceDynamic->SetScalarParameterValue(ParameterName, MetaVariable.Get<int>());
			break;

		case EMetaVariableType::Vector :
			MaterialInstanceDynamic->SetVectorParameterValue(ParameterName, MetaVariable.Get<FVector>());
			break;

		case EMetaVariableType::Vector4 :
			{
				FVector4 Vector4  = MetaVariable.Get<FVector4>();
				FLinearColor LinearColor;
				LinearColor.R = Vector4.X;
				LinearColor.G = Vector4.Y;
				LinearColor.B = Vector4.Z;
				LinearColor.A = Vector4.W;

				MaterialInstanceDynamic->SetVectorParameterValue(ParameterName, LinearColor);
			}
			break;

		case EMetaVariableType::LinearColor :
			MaterialInstanceDynamic->SetVectorParameterValue(ParameterName, MetaVariable.Get<FLinearColor>());
			break;
		}

		return true;
	}
	
	return false;
}

TMetaVariable FMaterialInstanceVariable::GetMaterialInstanceParameter(UPrimitiveComponent* PrimitiveComponent) const
{
	UMaterialInstanceDynamic* MaterialInstanceDynamic = PrimitiveComponent->CreateDynamicMaterialInstance(DynamicMaterialInstanceElementIndex);

	if(IsValid(MaterialInstanceDynamic))
	{
		return GetMaterialInstanceParameter(MaterialInstanceDynamic);
	}

	return TMetaVariable();
}

TMetaVariable FMaterialInstanceVariable::GetMaterialInstanceParameter(
	UMaterialInstanceDynamic* MaterialInstanceDynamic) const
{
	TMetaVariable ReturnMetaVariable = TMetaVariable();
	EMetaVariableType MetaVariableType = BaseVariableMetaDataGroup.GetMetaVariableType();

	float Sclar;
	FVector Vector;
	FLinearColor LinearColor;
	FVector4 Vector4;
	
	switch (MetaVariableType)
	{
	case EMetaVariableType::Bool:
	case EMetaVariableType::Float :
	case EMetaVariableType::Int :
		MaterialInstanceDynamic->GetScalarParameterValue(ParameterName, Sclar);
		ReturnMetaVariable.Set<float>(Sclar);
		break;

	case EMetaVariableType::Vector :
		MaterialInstanceDynamic->GetVectorParameterValue(ParameterName, LinearColor);

		Vector.X = LinearColor.R;
		Vector.Y = LinearColor.G;
		Vector.Z = LinearColor.B;
		
		ReturnMetaVariable.Set<FVector>(Vector);
		break;

	case EMetaVariableType::Vector4 :
		MaterialInstanceDynamic->GetVectorParameterValue(ParameterName, LinearColor);

		Vector4.X = LinearColor.R;
		Vector4.Y = LinearColor.G;
		Vector4.Z = LinearColor.B;
		Vector4.W = LinearColor.A;
		
		ReturnMetaVariable.Set<FVector4>(Vector4);
		break;
		
	case EMetaVariableType::LinearColor :
		MaterialInstanceDynamic->GetVectorParameterValue(ParameterName, LinearColor);
		ReturnMetaVariable.Set<FLinearColor>(LinearColor);
		break;
	}

	return ReturnMetaVariable;
}
