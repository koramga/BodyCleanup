// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TriggerActorComponent.h"
#include "TimerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API UTimerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()

protected:
	bool			bIsTriggerDestroy = false;
	FTimerHandle	TimerHandle;

	//주기를 설정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|TimerComponent")
	float			CycleTime = 1.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(bool bInputIsOnTrigger) override;

private:
	void __AdvanceTimer();
};
