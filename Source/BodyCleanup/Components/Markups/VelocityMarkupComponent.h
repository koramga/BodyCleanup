// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MarkupComponent.h"
#include "VelocityMarkupComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Markup), meta = (BlueprintSpawnableComponent))
class BODYCLEANUP_API UVelocityMarkupComponent : public UMarkupComponent
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|VelocityMarkupComponent")
	FVector		LinearVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|VelocityMarkupComponent")
	FVector		AngularVelocity;

public :
	FVector GetLinearVelocity() const;
	FVector GetAngularVelocity() const;
	virtual ELevelMarkupType	GetLevelMarkupType() const override;
	virtual void UpdateFromMarkup(UObject* Object) const override;
};
