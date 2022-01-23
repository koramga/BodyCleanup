// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VariableMetaData.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EVariableType : uint8
{
	Vector,
	Vector4,
	Color,
	Float,
	Int,
	Bool,
};

UENUM(BlueprintType)
enum class EVariableMetaDataType : uint8
{
	Normal,
	Range,
};

//USTRUCT(BlueprintType, Blueprintable)
//struct FVariableMetaData
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
//	EVariableType			VariableType = EVariableType::Float;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Vector", EditConditionHides))
//	FVector					VectorValue;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Vector4", EditConditionHides))
//	FVector4				Vector4Value;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Color", EditConditionHides))
//	FColor					ColorValue;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Float", EditConditionHides))
//	float					FloatValue;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Int", EditConditionHides))
//	int32					IntValue;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Bool", EditConditionHides))
//	bool					BoolValue;
//};
//
//
//USTRUCT(BlueprintType, Blueprintable)
//struct FVariableRangeMetaData
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
//	EVariableType			VariableType = EVariableType::Float;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Vector", EditConditionHides))
//	FVector					VectorValueFrom;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Vector", EditConditionHides))
//	FVector					VectorValueTo;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Vector4", EditConditionHides))
//	FVector4				Vector4ValueFrom;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Vector4", EditConditionHides))
//	FVector4				Vector4ValueTo;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Color", EditConditionHides))
//	FColor					ColorValueFrom;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Color", EditConditionHides))
//	FColor					ColorValueTo;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Float", EditConditionHides))
//	float					FloatValueFrom;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Float", EditConditionHides))
//	float					FloatValueTo;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Int", EditConditionHides))
//	int32					IntValueFrom;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable", meta = (EditCondition = "VariableType == EVariableType::Int", EditConditionHides))
//	int32					IntValueTo;
//};

UCLASS()
class METATOOLS_API UVariableMetaData : public UObject
{
	GENERATED_BODY()

public :
	UVariableMetaData();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EVariableMetaDataType		VariableMetaDataType;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "VariableMetaDataType == EVariableMetaDataType::Normal", EditConditionHides))
	//FVariableMetaData			VariableMetaData;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "VariableMetaDataType == EVariableMetaDataType::Range", EditConditionHides))
	//FVariableRangeMetaData		VariableRangeMetaData;

public :
	EVariableMetaDataType GetVariableMetaData() const;

};
