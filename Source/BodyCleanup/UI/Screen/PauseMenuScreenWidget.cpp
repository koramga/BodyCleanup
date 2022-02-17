// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuScreenWidget.h"

#include "BodyCleanup/Game/GameMode/MainGameModeBase.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenuScreenWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	ButtonGameContinue = Cast<UButton>(GetWidgetFromName(TEXT("BtnGameContinue")));
	ButtonGameSetting = Cast<UButton>(GetWidgetFromName(TEXT("BtnGameSetting")));
	ButtonBackToTitle = Cast<UButton>(GetWidgetFromName(TEXT("BtnBackToTitle")));
}

void UPauseMenuScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(IsValid(ButtonGameContinue))
	{
		ButtonGameContinue->OnClicked.AddDynamic(this, &UPauseMenuScreenWidget::__OnClickedGameContinue);
	}

	if(IsValid(ButtonGameSetting))
	{
		ButtonGameSetting->OnClicked.AddDynamic(this, &UPauseMenuScreenWidget::__OnClickedGameSetting);
	}

	if(IsValid(ButtonBackToTitle))
	{
		ButtonBackToTitle->OnClicked.AddDynamic(this, &UPauseMenuScreenWidget::__OnClickedBackToTitle);
	}
}

void UPauseMenuScreenWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPauseMenuScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UPauseMenuScreenWidget::__OnClickedGameContinue()
{
	AMainGameModeBase* MainGameModeBase = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());

	if(IsValid(MainGameModeBase))
	{
		MainGameModeBase->SetEnablePauseMenu(false);
	}
}

void UPauseMenuScreenWidget::__OnClickedGameSetting()
{
}

void UPauseMenuScreenWidget::__OnClickedBackToTitle()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("LV_MainMenu"));
}
