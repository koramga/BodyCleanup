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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|Patrol", meta = (EditCondition = "PatrolType != EBTPatrolType::None", EditConditionHides))
	TArray<class ABasePatrolActor*>		PatrolActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|Patrol", meta = (EditCondition = "PatrolType == EBTPatrolType::Space", EditConditionHides))
	FFloatVariableMetaData				MinPatrolDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|Patrol", meta = (EditCondition = "PatrolType == EBTPatrolType::Space", EditConditionHides))
	FFloatVariableMetaData				MaxPatrolDistance;

	int32	PatrolActorIndex = 0;
	int32	PatrolActorDirection = 1;

	TArray<TSoftObjectPtr<UPrimitiveComponent>> AttackPrimitiveComponents;
	TMap<TSoftObjectPtr<UPrimitiveComponent>, TArray<TWeakObjectPtr<AActor>>> AttackPrimitiveComponentOverlapMap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void __OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void UpdateDeath(bool bInIsDeath) override;
	virtual void OnChangeOfStateFromNotify(FAnimNotify_ChangeOfStateStruct& InNotifyStruct) override;
	
public :
	virtual EBTPatrolType GetPatrolType() const override;
	virtual class IBTPatrolActorInterface* GetPatrolActorInterface() const override;
	virtual void SetNextPatrol() override;
	virtual FBTPatrolInfo GetPatrolInfo() const override;
};
