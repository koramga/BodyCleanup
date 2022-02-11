// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseActor.h"
#include "CharacterSuckingActor.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ACharacterSuckingActor : public ABaseActor
{
	GENERATED_BODY()

public :
	ACharacterSuckingActor();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent*	StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UInteractiveSuckingComponent* InteractiveSuckingComponent;

	FVector InitialLocation;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
