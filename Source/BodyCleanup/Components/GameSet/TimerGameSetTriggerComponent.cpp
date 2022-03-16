
// Fill out your copyright notice in the Description page of Project Settings.

#include "TimerGameSetTriggerComponent.h"
#include "BodyCleanup/Game/GameMode/MainGameModeBase.h"
#include "BodyCleanup/UI/Screen/MainScreenWidget.h"

UTimerGameSetTriggerComponent::UTimerGameSetTriggerComponent()
{

}

void UTimerGameSetTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	if (InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		AMainGameModeBase* MainGameModeBase = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());
		MainGameModeBase->OnLevelStartDelegate.BindUFunction(this, FName("TimerStart"));
		MainGameModeBase->OnLevelStartDelegate.ExecuteIfBound(this);
	}
}

void UTimerGameSetTriggerComponent::TimerStart()
{
	AMainGameModeBase* MainGameModeBase = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());
	MainGameModeBase->GetMainScreenWidget()->StartTimer();
}

void UTimerGameSetTriggerComponent::TimerEnd()
{

}
