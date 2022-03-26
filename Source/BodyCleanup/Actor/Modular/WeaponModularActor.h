// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseModularActor.h"
#include "WeaponModularActor.generated.h"

UCLASS()
class BODYCLEANUP_API AWeaponModularActor : public ABaseModularActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponModularActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|WeaponModularActor")
	TSubclassOf<class UCAPAbility>		GeneralAttackCAPAbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|WeaponModularActor")
	TSubclassOf<class UCAPAbility>		ChargeAttackCAPAbilityClass;
};
