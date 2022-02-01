// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../BaseAIController.h"
#include "BaseMonsterController.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ABaseMonsterController : public ABaseAIController
{
	GENERATED_BODY()
	
public :
	ABaseMonsterController();
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public :
	virtual void Tick(float DeltaTime) override;	
};
