// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MarkupComponent.h"
#include "MetaTools/Variable/Classes/VectorVariableMetaData.h"
#include "VelocityMarkupComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Markup), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API UVelocityMarkupComponent : public UMarkupComponent
{
	GENERATED_BODY()

public :
	UVelocityMarkupComponent();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|VelocityMarkupComponent")
	FVectorVariableMetaData		LinearVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|VelocityMarkupComponent")
	FVectorVariableMetaData		AngularVelocity;

public :
	FVector GetLinearVelocity() const;
	FVector GetAngularVelocity() const;
	virtual ELevelMarkupType	GetLevelMarkupType() const override;
	virtual void UpdateFromMarkup(UObject* Object) const override;
};
