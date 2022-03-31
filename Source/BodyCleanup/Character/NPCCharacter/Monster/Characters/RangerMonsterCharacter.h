// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyCleanup/Character/NPCCharacter/Monster/BaseMonsterCharacter.h"
#include "GameFramework/Actor.h"
#include "RangerMonsterCharacter.generated.h"

UCLASS()
class BODYCLEANUP_API ARangerMonsterCharacter : public ABaseMonsterCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARangerMonsterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
