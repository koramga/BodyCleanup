// Fill out your copyright notice in the Description page of Project Settings.


#include "CorpseElementWidget.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"

void UCorpseElementWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextCorpseCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextCorpseCount")));
	BorderBackground = Cast<UBorder>(GetWidgetFromName(TEXT("BorderBackground")));
}

void UCorpseElementWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	MaxCorpseCount = 0;
	CurrentCorpseCount = 0;

	if(IsValid(BorderBackground))
	{
		DefaultBackgroundColor = BorderBackground->BrushColor;
	}

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
		
		TextCorpseCount->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), CurrentCorpseCount, MaxCorpseCount)));		
	}
	else
	{
		TextCorpseCount->SetText(FText::FromString(FString::Printf(TEXT("-- / --"))));
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

	if(CurrentCorpseCount >= MaxCorpseCount)
	{
		if(IsValid(BorderBackground))
		{
			BorderBackground->SetBrushColor(SuccessBackgroundColor);
		}

		if(IsValid(SuccessSoundWave))
		{
			UGameplayStatics::PlaySound2D(this, SuccessSoundWave);
		}
	}

	__SetCorpseText();
}

void UCorpseElementWidget::ResetCorpseCount()
{
	CurrentCorpseCount = 0;

	if(IsValid(BorderBackground))
	{
		BorderBackground->SetBrushColor(DefaultBackgroundColor);
	}

	__SetCorpseText();
}
