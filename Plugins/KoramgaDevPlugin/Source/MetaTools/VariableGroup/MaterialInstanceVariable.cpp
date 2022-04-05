// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialInstanceVariable.h"

bool FMaterialInstanceVariable::SetMaterialInstanceParameter(USkeletalMeshComponent* SkeletalMeshComponent) const
{
	UMaterialInstanceDynamic* MaterialInstanceDynamic = SkeletalMeshComponent->CreateDynamicMaterialInstance(DynamicMaterialInstanceElementIndex);

	if(IsValid(MaterialInstanceDynamic))
	{
		return SetMaterialInstanceParameter(MaterialInstanceDynamic);
	}

	return false;
}

bool FMaterialInstanceVariable::SetMaterialInstanceParameter(UMaterialInstanceDynamic* MaterialInstanceDynamic) const
{
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
	
}