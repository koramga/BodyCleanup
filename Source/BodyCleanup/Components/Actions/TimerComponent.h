// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ActionComponent.h"
#include "TimerComponent.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UTimerComponent : public UActionComponent
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

private:
	virtual void OnTrigger(bool bInputIsOnTrigger) override;

private:
	void __AdvanceTimer();
};
