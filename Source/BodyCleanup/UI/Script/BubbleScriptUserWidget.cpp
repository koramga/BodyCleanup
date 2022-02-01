// Fill out your copyright notice in the Description page of Project Settings.


#include "BubbleScriptUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"

void UBubbleScriptUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	TextBlockScript = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlockScript")));
	BorderBackground = Cast<UBorder>(GetWidgetFromName(TEXT("BorderBackground")));
	ImageSpeaker = Cast<UImage>(GetWidgetFromName(TEXT("ImageSpeaker")));
}

void UBubbleScriptUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBubbleScriptUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBubbleScriptUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(IsVisible())
	{
		FVector2D ScriptTextBlockSize = TextBlockScript->GetDesiredSize();

		UCanvasPanelSlot* BorderBackgroundCanvasPanelSlot = Cast<UCanvasPanelSlot>(BorderBackground->Slot);

		if(IsValid(BorderBackgroundCanvasPanelSlot))
		{
			BorderBackgroundCanvasPanelSlot->SetSize(ScriptTextBlockSize);
		}

		UCanvasPanelSlot* ImageSpeakerCanvasPanelSlot = Cast<UCanvasPanelSlot>(ImageSpeaker->Slot);

		if(IsValid(ImageSpeakerCanvasPanelSlot))
		{
			ImageSpeakerCanvasPanelSlot->SetPosition(FVector2D(0.f, ScriptTextBlockSize.Y / 2.f));
		}		
	}
}

void UBubbleScriptUserWidget::SetText(const FString& String)
{
	TextBlockScript->SetText(FText::FromString(String));
}
