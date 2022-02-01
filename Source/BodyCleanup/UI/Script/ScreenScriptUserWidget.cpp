// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenScriptUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UScreenScriptUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	TextBlockSpeaker = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlockSpeaker")));
	TextBlockScript = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlockScript")));
	BorderBackground = Cast<UBorder>(GetWidgetFromName(TEXT("BorderBackground")));
}

void UScreenScriptUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UScreenScriptUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UScreenScriptUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UScreenScriptUserWidget::SetText(const FString& Speaker, const FString& Text)
{
	TextBlockSpeaker->SetText(FText::FromString(Speaker));
	TextBlockScript->SetText(FText::FromString(Text));
}
