// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyTriggerComponent.h"
#include "GameFramework/GameModeBase.h"
#include "../../../GameMode/LevelToolsGameModeBase.h"

UDestroyTriggerComponent::UDestroyTriggerComponent()
{
	//bIsCanControlTriggerComponentFromType = false;
	
	LevelTriggerInputFrom.LevelTriggerInputNodeFromType = ELevelTriggerInputNodeFromType::Action;
}

void UDestroyTriggerComponent::BeginPlay()
{
	Super::BeginPlay();


	ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GetWorld()->GetAuthGameMode());

	GetOwner()->OnDestroyed.AddDynamic(this, &UDestroyTriggerComponent::OnActorDestroyed);

	bIsTriggerDestroy = false;
}

void UDestroyTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();
}

void UDestroyTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);
}

void UDestroyTriggerComponent::OnActorDestroyed(AActor* DestroyedActor)
{
	if (false == bIsTriggerDestroy)
	{
		bIsTriggerDestroy = true;

		ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GetWorld()->GetAuthGameMode());

		if (nullptr != LevelToolsGameModeBase)
		{
			LevelToolsGameModeBase->UpdateTrigger(this, true);
		}
	}
}