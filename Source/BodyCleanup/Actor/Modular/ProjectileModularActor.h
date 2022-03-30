// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseModularActor.h"
#include "GameFramework/Actor.h"
#include "ProjectileModularActor.generated.h"

UCLASS()
class BODYCLEANUP_API AProjectileModularActor : public ABaseModularActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileModularActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float		SpeedPerSecond = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float		DeathTime = 5.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};