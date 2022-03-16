// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelDesignerTools/Trigger/Classes/Actor/GameSetTriggerComponent.h"
#include "TimerGameSetTriggerComponent.generated.h"


UCLASS( ClassGroup=(GameSet), meta=(BlueprintSpawnableComponent) )
class BODYCLEANUP_API UTimerGameSetTriggerComponent : public UGameSetTriggerComponent
{
	GENERATED_BODY()

public:
	UTimerGameSetTriggerComponent();

protected:
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;

	UFUNCTION()
		void TimerStart();

	UFUNCTION()
		void TimerEnd();
};
