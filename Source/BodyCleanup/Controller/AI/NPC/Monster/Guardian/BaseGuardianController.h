// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyCleanup/Controller/AI/NPC/Monster/BaseMonsterController.h"
#include "BaseGuardianController.generated.h"

UCLASS()
class BODYCLEANUP_API ABaseGuardianController : public ABaseMonsterController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseGuardianController();
	
protected:
	virtual void InitializeBlackboardData() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public :
	virtual void Tick(float DeltaTime) override;	
};
