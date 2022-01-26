// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathTriggerComponent.h"
#include "GameFramework/GameModeBase.h"
#include "../../../GameMode/LevelToolsGameModeBase.h"
#include "../../../Actor/LevelToolsActor.h"

UDeathTriggerComponent::UDeathTriggerComponent()
{
	LevelTriggerInputFrom.LevelTriggerInputNodeFromType = ELevelTriggerInputNodeFromType::Action;
}

void UDeathTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (Owner->GetClass()->ImplementsInterface(ULevelTriggerActorAssist::StaticClass()))
	{
		ILevelToolsActor* LevelToolsActor = Cast<ILevelToolsActor>(Owner);

		if (nullptr != LevelToolsActor)
		{
			ULevelTriggerActorAssist* LevelTriggerActorAssist = LevelToolsActor->GetLevelTriggerActorAssist();

			if (IsValid(LevelTriggerActorAssist))
			{
				LevelTriggerActorAssist->RegisterTrigger(this);
			}
		}
	}
}

void UDeathTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();
}

void UDeathTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);
}

void UDeathTriggerComponent::UpdateAction(const FLevelTriggerUpdateActionParam& LevelTriggerUpdateActionParam)
{
	Super::UpdateAction(LevelTriggerUpdateActionParam);

	ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GetWorld()->GetAuthGameMode());

	if (nullptr != LevelToolsGameModeBase)
	{
		LevelToolsGameModeBase->UpdateTrigger(this, LevelTriggerUpdateActionParam.bIsOnTrigger);
	}
}
