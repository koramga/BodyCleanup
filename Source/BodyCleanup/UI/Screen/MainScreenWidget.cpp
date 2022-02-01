// Fill out your copyright notice in the Description page of Project Settings.


#include "MainScreenWidget.h"
#include "../Script/ScreenScriptUserWidget.h"
#include "../Script/ScreenSelectScriptUserWidget.h"

void UMainScreenWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	ScreenScriptUserWidget = Cast<UScreenScriptUserWidget>(GetWidgetFromName(TEXT("UI_ScreenScript")));
}

void UMainScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(IsValid(ScreenScriptUserWidget))
	{
		ScreenScriptUserWidget->SetHiddenInGame(true);
	}
}

void UMainScreenWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMainScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMainScreenWidget::SetHiddenInGameScreenScript(bool bIsHiddenInGame)
{
	if(IsValid(ScreenScriptUserWidget))
	{
		ScreenScriptUserWidget->SetHiddenInGame(bIsHiddenInGame);
	}
}

void UMainScreenWidget::SetScreenScriptText(const FString& Speaker, const FString& Text)
{
	if(IsValid(ScreenScriptUserWidget))
	{
		ScreenScriptUserWidget->SetText(Speaker, Text);
	}	
}
