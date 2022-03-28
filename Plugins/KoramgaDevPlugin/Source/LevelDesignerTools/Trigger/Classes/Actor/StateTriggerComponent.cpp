// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTriggerComponent.h"
#include "GameFramework/GameModeBase.h"
#include "../../../GameMode/LevelToolsGameModeBase.h"

UStateTriggerComponent::UStateTriggerComponent()
{

}

void UStateTriggerComponent::AddTriggerState(uint8 TriggerState)
{
	TriggerStates.Add(TriggerState);
}

void UStateTriggerComponent::RemoveTriggerState(uint8 TriggerState)
{
	TriggerStates.Remove(TriggerState);
}

void UStateTriggerComponent::UpdateTriggerState(uint8 UpdateTriggerState)
{
	for (uint8 TriggerState : TriggerStates)
	{
		if (TriggerState == UpdateTriggerState)
		{
			if (GetWorld()->GetAuthGameMode()->GetClass()->ImplementsInterface(ULevelToolsGameModeBase::StaticClass()))
			{
				ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GetWorld()->GetAuthGameMode());

				if (nullptr != LevelToolsGameModeBase)
				{
					LevelToolsGameModeBase->UpdateTriggerOnce(this);
				}
			}
		}
	}
}
