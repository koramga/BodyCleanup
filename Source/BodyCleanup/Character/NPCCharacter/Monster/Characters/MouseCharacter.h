// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseMonsterCharacter.h"
#include "MouseCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API AMouseCharacter : public ABaseMonsterCharacter
{
	GENERATED_BODY()
	
public :
	AMouseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
