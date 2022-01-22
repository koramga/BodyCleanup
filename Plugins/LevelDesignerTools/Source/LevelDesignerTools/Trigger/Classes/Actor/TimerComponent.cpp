// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerComponent.h"
#include "GameFramework/GameModeBase.h"
#include "../../../GameMode/LevelToolsGameModeBase.h"

UTimerComponent::UTimerComponent()
{
	LevelTriggerInputFrom.LevelTriggerInputNodeFromType = ELevelTriggerInputNodeFromType::Action;
}

void UTimerComponent::BeginPlay()
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

void UTimerComponent::SetupTrigger()
{
	Super::SetupTrigger();
}

void UTimerComponent::UpdateTrigger(bool bInputIsOnTrigger)
{
	Super::UpdateTrigger(bInputIsOnTrigger);

	if (true == bInputIsOnTrigger)
	{
		__CreateTimer();
	}
	else
	{
		__DestroyTimer();
	}
}

void UTimerComponent::__CreateTimer()
{
	if (false == bIsCreateTimer)
	{
		bIsCreateTimer = true;
		GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UTimerComponent::__AdvanceTimer, CycleTime, true);
	}
}

void UTimerComponent::__DestroyTimer()
{
	if (bIsCreateTimer)
	{
		bIsCreateTimer = false;
		GetOwner()->GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void UTimerComponent::__AdvanceTimer()
{
	if (GetWorld()->GetAuthGameMode()->GetClass()->ImplementsInterface(ULevelToolsGameModeBase::StaticClass()))
	{
		ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GetWorld()->GetAuthGameMode());

		if (nullptr != LevelToolsGameModeBase)
		{
			LevelToolsGameModeBase->UpdateTriggerOnce(this, false);
		}
	}
}