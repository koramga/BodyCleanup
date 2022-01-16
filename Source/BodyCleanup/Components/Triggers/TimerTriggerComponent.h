// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TriggerComponent.h"
#include "TimerTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class BODYCLEANUP_API UTimerTriggerComponent : public UTriggerComponent
{
	GENERATED_BODY()

public:
	UTimerTriggerComponent();

protected:
	bool			bIsTriggerDestroy = false;
	FTimerHandle	TimerHandle;

	//주기에 맞게 지속적으로 Trigger를 호출할지 여부입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|TimerTriggerComponent")
	bool			bIsLoopCycle = false;

	//주기를 설정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|TimerTriggerComponent")
	float			CycleTime = 1.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private :
	void __AdvanceTimer();
};
