// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "InteractiveMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BODYCLEANUP_API UInteractiveMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractiveMovementComponent();

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EInteractiveAction		InteractiveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EInteractiveType		InteractiveType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					AbsorbingInterpValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTransform				InteractiveTransform;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	EInteractiveAction	GetInteractiveAction()	const;
	EInteractiveType	GetInteractiveType()	const;

public :
	void SetInteractiveAction(EInteractiveAction InputInteractiveAction);
	void SetInteractiveTransform(const FTransform& Transform);
	//void SetInteractiveLocation()
};