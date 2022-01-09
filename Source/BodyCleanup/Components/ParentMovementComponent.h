// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "Components/SceneComponent.h"
#include "ParentMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BODYCLEANUP_API UParentMovementComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UParentMovementComponent();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	InterpSpeed = 1.f;

	UPROPERTY(VisibleAnywhere)
	FTransform	DestinationTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	bIsUpdateLocation = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	bIsUpdateRotator = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	bIsUpdateScale = true;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
