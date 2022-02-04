// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAPAttributeSet.generated.h"


USTRUCT(BlueprintType)
struct FCAPAttributeData
{
	GENERATED_BODY()

	public :
		FCAPAttributeData()
			: BaseValue(0.f), CurrentValue(0.f){}

	FCAPAttributeData(const FName& AttributeName)
		: AttributeName(AttributeName) {}

	virtual ~FCAPAttributeData(){}

	float GetCurrentValue() const { return CurrentValue; }
	void SetCurrentValue(float InValue) {CurrentValue = InValue;}
	float GetBaseValue() const {return BaseValue;}
	void SetBaseValue(float InValue) {BaseValue = InValue;}
	FName GetAttributeName() const {return AttributeName;}
	void SetAttributeName(const FName& InAttributeName) {AttributeName = InAttributeName;}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	BaseValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	CurrentValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName	AttributeName;
};

//#define CAPATTRIBUTE_VALUE_GETTER(PropertyName) \
//	FORCEINLINE float Get##PropertyName() const \
//	{ \
//		return PropertyName.GetCurrentValue(); \
//	}
//
//#define CAPATTRIBUTE_NAME_GETTER(PropertyName) \
//	FORCEINLINE FName Get##PropertyName##Name() const \
//	{ \
//		return PropertyName.GetAttributeName(); \
//	}
//
//#define CAPATTRIBUTE_VALUE_SETTER(PropertyName) \
//	FORCEINLINE void Set##PropertyName##(float InValue) \
//	{\
//		PropertyName.SetCurrentValue(InValue);\
//	}
//#define CAPATTRIBUTE_VALUE_INITTER(PropertyName) \
//	FORCEINLINE void Init##PropertyName##(float InValue)\
//	{\
//		PropertyName.SetCurrentValue(InValue); \
//		PropertyName.SetBaseValue(InValue); \
//	}
//		
//
//#define CAPATTRIBUTE_VALUE_CREATE(PropertyName) \
//	FBaseCAPAttributeData PropertyName = FBaseCAPAttributeData(#PropertyName);
//
//#define CAPATTRIBUTE_VALUE_CREATER(ClassName, PropertyName) \
//	CAPATTRIBUTE_VALUE_CREATE(PropertyName)	\
//	CAPATTRIBUTE_VALUE_GETTER(PropertyName) \
//	CAPATTRIBUTE_NAME_GETTER(PropertyName) \
//	CAPATTRIBUTE_VALUE_SETTER(PropertyName) \
//	CAPATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS(DefaultToInstanced, Blueprintable)
class GAMECAPABILITYSYSTEM_API UCAPAttributeSet : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup")	
	TArray<FCAPAttributeData>	CapAttributeDatas;
	
};
