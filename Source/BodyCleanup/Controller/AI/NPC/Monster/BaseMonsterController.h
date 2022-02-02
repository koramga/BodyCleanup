// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNPCController.h"
#include "BodyCleanup/Character/NPCCharacter/BaseNPCCharacter.h"
#include "BaseMonsterController.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ABaseMonsterController : public ABaseNPCController
{
	GENERATED_BODY()
	
public :
	ABaseMonsterController();

protected: 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|BaseMonsterController")
	FFloatVariableMetaData					TraceRange;
	
protected:
	virtual void InitializeBlackboardData() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public :
	virtual void Tick(float DeltaTime) override;	
};
