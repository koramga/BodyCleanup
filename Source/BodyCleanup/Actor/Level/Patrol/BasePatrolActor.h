// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseLevelActor.h"
#include "Interface/BTPatrolActorInterface.h"
#include "BasePatrolActor.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ABasePatrolActor : public ABaseLevelActor, public IBTPatrolActorInterface
{
	GENERATED_BODY()

public :
	ABasePatrolActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent*	BoxComponent;

protected: 
	virtual void BeginPlay() override;

public :
	virtual void Tick(float DeltaSeconds) override;

public :
	virtual bool IsGoal(const AActor* InActor) const override;
	virtual FVector GetGoalPosition() const override;
	virtual bool IsPointInActor(const FVector& InVector) const override;
};