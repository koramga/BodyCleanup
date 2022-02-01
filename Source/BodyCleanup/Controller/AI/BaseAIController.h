// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ExDefines.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
	
public :
	ABaseAIController();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|BaseAIController")
	class UBehaviorTree*					BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|BaseAIController")
	class UBlackboardData*					BlackboardData;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public :
	virtual void Tick(float DeltaTime) override;
};
