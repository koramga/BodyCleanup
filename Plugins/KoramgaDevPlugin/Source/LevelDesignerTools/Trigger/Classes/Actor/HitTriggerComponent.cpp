// Fill out your copyright notice in the Description page of Project Settings.


#include "HitTriggerComponent.h"

#include "LevelDesignerTools/Actor/LevelToolsActorInterface.h"
#include "GameFramework/GameModeBase.h"
#include "../../../GameMode/LevelToolsGameModeBase.h"
#include "../../../Actor/LevelToolsActorInterface.h"

UHitTriggerComponent::UHitTriggerComponent()
{
	LevelTriggerInputFrom.LevelTriggerInputNodeFromType = ELevelTriggerInputNodeFromType::Action;
}

void UHitTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (Owner->GetClass()->ImplementsInterface(ULevelToolsActorInterface::StaticClass()))
	{
		ILevelToolsActorInterface* LevelToolsActor = Cast<ILevelToolsActorInterface>(Owner);

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

void UHitTriggerComponent::UpdateAction(const FLevelTriggerUpdateActionParam& LevelTriggerUpdateActionParam)
{
	Super::UpdateAction(LevelTriggerUpdateActionParam);

	ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GetWorld()->GetAuthGameMode());

	if (nullptr != LevelToolsGameModeBase)
	{
		LevelToolsGameModeBase->UpdateTrigger(this, LevelTriggerUpdateActionParam.bIsOnTrigger);
	}
}
