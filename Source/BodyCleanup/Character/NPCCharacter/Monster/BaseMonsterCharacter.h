// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNPCCharacter.h"
#include "BaseMonsterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ABaseMonsterCharacter : public ABaseNPCCharacter
{
	GENERATED_BODY()
	
public :
	ABaseMonsterCharacter();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private :
	void __OverlapSuperJump(AActor* Actor);
};
