// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "../../UI/Screen/MainScreenWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../../Controller/Player/BasePlayerController.h"

void AMainGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(BaseScreenWidget))
	{
		MainScreenWidget = Cast<UMainScreenWidget>(BaseScreenWidget);
	}
}

TSoftObjectPtr<UMainScreenWidget> AMainGameModeBase::GetMainScreenWidget() const
{
	return Cast<UMainScreenWidget>(MainScreenWidget);
}
