// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTriggerActorAssist.h"
#include "../../Trigger/Interfaces/LevelTriggerInterface.h"
#include "../../Trigger/Classes/Actor/DeathTriggerComponent.h"
#include "LevelDesignerTools/Trigger/Classes/Actor/HitTriggerComponent.h"

void ULevelTriggerActorAssist::RegisterTrigger(ILevelTriggerInterface* LevelTriggerInterface)
{
	if (nullptr != LevelTriggerInterface)
	{
		LevelTriggerInterfaces.Add(Cast<UObject>(LevelTriggerInterface));
	}
}

void ULevelTriggerActorAssist::SetLevelTriggerState(ELevelTriggerActorState LevelTriggerActorState, bool bIsState)
{
	if (ELevelTriggerActorState::Death == LevelTriggerActorState)
	{
		FLevelTriggerUpdateActionParam UpdateActionParam;
		UpdateActionParam.bIsOnTrigger = bIsState;

		for (TSoftObjectPtr<UObject>& LevelTriggerInterface : LevelTriggerInterfaces)
		{
			UDeathTriggerComponent* DeathTriggerComponent = Cast<UDeathTriggerComponent>(LevelTriggerInterface.Get());

			if (IsValid(DeathTriggerComponent))
			{
				DeathTriggerComponent->UpdateAction(UpdateActionParam);
			}
		}
	}
	if (ELevelTriggerActorState::Hit == LevelTriggerActorState)
	{
		FLevelTriggerUpdateActionParam UpdateActionParam;
		UpdateActionParam.bIsOnTrigger = bIsState;

		for (TSoftObjectPtr<UObject>& LevelTriggerInterface : LevelTriggerInterfaces)
		{
			UHitTriggerComponent* HitTriggerComponent = Cast<UHitTriggerComponent>(LevelTriggerInterface.Get());

			if (IsValid(HitTriggerComponent))
			{
				HitTriggerComponent->UpdateAction(UpdateActionParam);
			}
		}
	}
}

void ULevelTriggerActorAssist::SetLevelTriggerStateOnce(ELevelTriggerActorState LevelTriggerActorState)
{
	SetLevelTriggerState(LevelTriggerActorState, true);
	SetLevelTriggerState(LevelTriggerActorState, false);
}
