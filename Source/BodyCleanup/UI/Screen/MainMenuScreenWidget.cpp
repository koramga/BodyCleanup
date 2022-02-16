// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuScreenWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuScreenWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	ButtonGameStart = Cast<UButton>(GetWidgetFromName(TEXT("BtnGameStart")));
	ButtonGameExit = Cast<UButton>(GetWidgetFromName(TEXT("BtnGameExit")));
}

void UMainMenuScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(IsValid(ButtonGameStart))
	{
		ButtonGameStart->OnClicked.AddDynamic(this, &UMainMenuScreenWidget::__OnGameStart);
	}

	if(IsValid(ButtonGameExit))
	{
		ButtonGameExit->OnClicked.AddDynamic(this, &UMainMenuScreenWidget::__OnGameExit);
	}
}

void UMainMenuScreenWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMainMenuScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMainMenuScreenWidget::__OnGameStart()
{
	UGameplayStatics::OpenLevel(GetWorld(), GameStartLevelName);
}

void UMainMenuScreenWidget::__OnGameExit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}