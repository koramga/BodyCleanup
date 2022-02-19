// Fill out your copyright notice in the Description page of Project Settings.


#include "CorpseElementWidget.h"
#include "Components/TextBlock.h"

void UCorpseElementWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextCorpseCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextCorpseCount")));
}

void UCorpseElementWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	MaxCorpseCount = 0;
	CurrentCorpseCount = 0;

	__SetCorpseText();
}

void UCorpseElementWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCorpseElementWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCorpseElementWidget::__SetCorpseText()
{
	if(MaxCorpseCount > 0)
	{
		if(IsHiddenInGame())
		{
			SetHiddenInGame(false);
		}
		
		TextCorpseCount->SetText(FText::FromString(FString::Printf(TEXT("%d : %d"), CurrentCorpseCount, MaxCorpseCount)));		
	}
	else
	{
		SetHiddenInGame(true);
	}	
}

void UCorpseElementWidget::SetMaxCorpseCount(int32 CorpseCount)
{
	MaxCorpseCount = CorpseCount;

	__SetCorpseText();
}

void UCorpseElementWidget::AddCorpseCount()
{
	CurrentCorpseCount++;

	__SetCorpseText();
}

void UCorpseElementWidget::ResetCorpseCount()
{
	CurrentCorpseCount = 0;

	__SetCorpseText();
}
