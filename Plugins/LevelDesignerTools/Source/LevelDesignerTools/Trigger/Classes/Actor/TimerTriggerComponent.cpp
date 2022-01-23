// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerTriggerComponent.h"
#include "GameFramework/GameModeBase.h"
#include "../../../GameMode/LevelToolsGameModeBase.h"

UTimerTriggerComponent::UTimerTriggerComponent()
{
	LevelTriggerInputFrom.LevelTriggerInputNodeFromType = ELevelTriggerInputNodeFromType::Action;
}

void UTimerTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()->GetAuthGameMode()->GetClass()->ImplementsInterface(ULevelToolsGameModeBase::StaticClass()))
	{
		ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GetWorld()->GetAuthGameMode());

		if (nullptr != LevelToolsGameModeBase)
		{
			const ULevelTriggerManager* LevelTriggerManager = LevelToolsGameModeBase->GetLevelTriggerManager();

			if (IsValid(LevelTriggerManager))
			{
				ULevelTriggerInterfaceSpace* LevelTriggerInterfaceSpace = LevelTriggerManager->GetLevelTriggerInterfaceSpace(this);

				if (IsValid(LevelTriggerInterfaceSpace))
				{
					if (false == LevelTriggerInterfaceSpace->HasTriggerComponents())
					{
						__CreateTimer();
					}
				}
			}
		}
	}

}

void UTimerTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();
}

void UTimerTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	if (true == InputLevelTriggerUpdateParam.bIsOnTriggers[DEFAULT_TRIGGER_INDEX])
	{
		__CreateTimer();
	}
	else
	{
		__DestroyTimer();
	}
}

void UTimerTriggerComponent::__CreateTimer()
{
	if (false == bIsCreateTimer)
	{
		bIsCreateTimer = true;
		GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UTimerTriggerComponent::__AdvanceTimer, CycleTime, true);
	}
}

void UTimerTriggerComponent::__DestroyTimer()
{
	if (bIsCreateTimer)
	{
		bIsCreateTimer = false;
		GetOwner()->GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void UTimerTriggerComponent::__AdvanceTimer()
{
	UE_LOG(LogTemp, Display, TEXT("__AdvanceTimer"));

	if (GetWorld()->GetAuthGameMode()->GetClass()->ImplementsInterface(ULevelToolsGameModeBase::StaticClass()))
	{
		ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GetWorld()->GetAuthGameMode());

		if (nullptr != LevelToolsGameModeBase)
		{
			LevelToolsGameModeBase->UpdateTriggerOnce(this);
		}
	}
}