// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "LevelDesignerTools/Markup/Interfaces/LevelMarkupInterface.h"
#include "Components/SceneComponent.h"
#include "MarkupComponent.generated.h"


UCLASS( ClassGroup=(Markup), meta=(BlueprintSpawnableComponent) )
class BODYCLEANUP_API UMarkupComponent : public USceneComponent, public ILevelMarkupInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMarkupComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
			
public :
	virtual ELevelMarkupType	GetLevelMarkupType() const override;
	virtual FVector GetMarkupLocation() const override;
	virtual FTransform GetMarkupTransform() const override;
	virtual void UpdateFromMarkup(UObject* Object) const override;
};
