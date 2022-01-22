// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerComponent.h"
#include "GameFramework/GameModeBase.h"
#include "../../../GameMode/LevelToolsGameModeBase.h"

void UTimerComponent::BeginPlay()
{
	Super::BeginPlay();
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
		GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UTimerComponent::__AdvanceTimer, CycleTime, true);
	}
	else
	{
		GetOwner()->GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void UTimerComponent::__AdvanceTimer()
{
	//�ð��� ��� ������ ���� ����� �ʿ��ϰڳ�


	if (GetWorld()->GetAuthGameMode()->GetClass()->ImplementsInterface(ULevelToolsGameModeBase::StaticClass()))
	{
		ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GetWorld()->GetAuthGameMode());

		if (nullptr != LevelToolsGameModeBase)
		{
			LevelToolsGameModeBase->UpdateTrigger(this, true);
			LevelToolsGameModeBase->UpdateTrigger(this, false);
		}
	}
}