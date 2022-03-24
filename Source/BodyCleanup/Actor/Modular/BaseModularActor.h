// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseModularActor.generated.h"

UCLASS()
class BODYCLEANUP_API ABaseModularActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseModularActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent*	BoxComponent;
};
