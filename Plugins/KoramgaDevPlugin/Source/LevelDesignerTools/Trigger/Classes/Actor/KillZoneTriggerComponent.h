// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerActorComponent.h"
#include "KillZoneTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API UKillZoneTriggerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()

public :
	UKillZoneTriggerComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|KillZoneTriggerComponent")
	TArray<TSoftObjectPtr<AActor>>	ExceptActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|KillZoneTriggerComponent")
	TArray<TSubclassOf<AActor>>		ExceptActorClasses;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;
};
