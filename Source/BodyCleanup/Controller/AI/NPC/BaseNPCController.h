// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseAIController.h"
#include "BaseNPCController.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ABaseNPCController : public ABaseAIController
{
	GENERATED_BODY()
	
public :
	ABaseNPCController();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|BaseNPCController")
	FFloatVariableMetaData					LookAroundTime;

protected:
	virtual void InitializeBlackboardData() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public :
	virtual void Tick(float DeltaTime) override;	
};
