// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "BaseNPCCharacter.generated.h"

/**
 * 
 */

UCLASS()
class BODYCLEANUP_API ABaseNPCCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public :
	ABaseNPCCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|Patrol")
	EBTPatrolType						PatrolType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|Patrol", meta = (EditCondition = "PatrolType != ENPCPatrolType::None", EditConditionHides))
	TArray<class ABasePatrolActor*>		PatrolActors;

	int32 PatrolActorIndex = 0;
	int32 PatrolActorDirection = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public :
	virtual EBTPatrolType GetPatrolType() const override;
	virtual class IBTPatrolActorInterface* GetPatrolActorInterface() const override;
	virtual void SetNextPatrol() override;
};
