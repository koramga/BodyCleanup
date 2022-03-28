// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TriggerActorComponent.h"
#include "TimerTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API UTimerTriggerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()

public :
	UTimerTriggerComponent();

protected:
	bool			bIsTriggerDestroy = false;
	bool			bIsCreateTimer = false;
	FTimerHandle	TimerHandle;

	//Cycle의 시간을 결정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|TimerTriggerComponent")
	float			CycleTime = 1.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;

private:
	void __CreateTimer();
	void __DestroyTimer();
	void __AdvanceTimer();
};
