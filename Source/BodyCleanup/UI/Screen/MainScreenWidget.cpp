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
		ScreenScriptUserWidget->SetVisibility(ESlateVisibility::Hidden);
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
