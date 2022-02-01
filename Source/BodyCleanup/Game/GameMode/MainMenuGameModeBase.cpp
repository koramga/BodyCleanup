// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameModeBase.h"

void AMainMenuGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AMainMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
