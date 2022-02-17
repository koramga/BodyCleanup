// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "../../UI/Screen/MainScreenWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../../Controller/Player/BasePlayerController.h"
#include "BodyCleanup/UI/Screen/PauseMenuScreenWidget.h"

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
	
	if(IsValid(PauseMenuScreenWidgetClass))
	{
		PauseMenuScreenWidget = CreateWidget<UPauseMenuScreenWidget>(GetWorld(), PauseMenuScreenWidgetClass);
		
		if (PauseMenuScreenWidget)
		{
			PauseMenuScreenWidget->AddToViewport();
			PauseMenuScreenWidget->SetHiddenInGame(true);
		}			
	}
}

TSoftObjectPtr<UMainScreenWidget> AMainGameModeBase::GetMainScreenWidget() const
{
	return Cast<UMainScreenWidget>(MainScreenWidget);
}

TSoftObjectPtr<UPauseMenuScreenWidget> AMainGameModeBase::GetPauseMenuScreenWidget() const
{
	return Cast<UPauseMenuScreenWidget>(PauseMenuScreenWidget);
}

void AMainGameModeBase::TogglePauseMenu()
{
	SetEnablePauseMenu(!IsEnablePauseMenu());
}

bool AMainGameModeBase::IsEnablePauseMenu()
{
	return UGameplayStatics::IsGamePaused(GetWorld());;
}

void AMainGameModeBase::SetEnablePauseMenu(bool bIsEnable)
{
	const bool bIsPauseGame = UGameplayStatics::IsGamePaused(GetWorld());

	if(bIsPauseGame != bIsEnable)
	{
		if(IsValid(PauseMenuScreenWidget))
		{
			PauseMenuScreenWidget->SetHiddenInGame(bIsPauseGame);
		}
	
		UGameplayStatics::SetGamePaused(GetWorld(), !bIsPauseGame);		
	}
}
