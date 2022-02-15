// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "../Interfaces/LevelMarkupInterface.h"
#include "CameraMarkupComponent.generated.h"

/**
 * 
 */
UCLASS()
class LEVELDESIGNERTOOLS_API UCameraMarkupComponent : public UCameraComponent, public ILevelMarkupInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCameraMarkupComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual ELevelMarkupType	GetLevelMarkupType() const override;
	virtual FVector GetMarkupLocation() const override;
	virtual FTransform GetMarkupTransform() const override;
	virtual void UpdateFromMarkup(UObject* Object) const override;
	
};
