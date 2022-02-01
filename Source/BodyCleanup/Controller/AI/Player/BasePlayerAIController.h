// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../BaseAIController.h"
#include "BasePlayerAIController.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ABasePlayerAIController : public ABaseAIController
{
	GENERATED_BODY()
	
public :
	ABasePlayerAIController();
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public :
	virtual void Tick(float DeltaTime) override;
};
