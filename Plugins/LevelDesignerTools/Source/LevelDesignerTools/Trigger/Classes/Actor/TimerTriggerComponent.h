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

	//주기를 설정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|TimerComponent")
	float			CycleTime = 1.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(bool bInputIsOnTrigger) override;

private:
	void __CreateTimer();
	void __DestroyTimer();
	void __AdvanceTimer();
};
