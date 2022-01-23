// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameModeBase.h"

ABaseGameModeBase::ABaseGameModeBase()
{
	//
}

void ABaseGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	LevelTriggerManager = NewObject<ULevelTriggerManager>(this);
}

void ABaseGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Display, TEXT("Koramga BeginPlay"));
	InitTrigger();
}

void ABaseGameModeBase::InitTrigger()
{
	LevelTriggerManager->BeginPlay();
}

void ABaseGameModeBase::RegisterTrigger(ILevelTriggerInterface* LevelTriggerInterface)
{
	LevelTriggerManager->RegisterTrigger(LevelTriggerInterface);
}

const ULevelTriggerManager* ABaseGameModeBase::GetLevelTriggerManager() const
{
	return LevelTriggerManager;
}

void ABaseGameModeBase::UpdateTrigger(class ILevelTriggerInterface* LevelTriggerInterface, bool bInputIsOnTrigger)
{
	LevelTriggerManager->UpdateTrigger(LevelTriggerInterface, bInputIsOnTrigger);
}

void ABaseGameModeBase::UpdateTriggerOnce(class ILevelTriggerInterface* LevelTriggerInterface)
{
	LevelTriggerManager->UpdateTriggerOnce(LevelTriggerInterface);
}