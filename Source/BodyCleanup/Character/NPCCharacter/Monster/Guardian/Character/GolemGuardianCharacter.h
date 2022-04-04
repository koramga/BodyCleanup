// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyCleanup/Character/NPCCharacter/Monster/Guardian/BaseGuardianCharacter.h"
#include "GolemGuardianCharacter.generated.h"

UCLASS()
class BODYCLEANUP_API AGolemGuardianCharacter : public ABaseGuardianCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGolemGuardianCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnHit(const FOnCAPAttributeChangeData& Data) override;;

protected:
	int		CurrentPhase = 0;
};
