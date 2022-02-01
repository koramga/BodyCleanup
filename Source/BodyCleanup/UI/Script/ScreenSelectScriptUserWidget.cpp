// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenSelectScriptUserWidget.h"

#include "Components/Border.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UScreenSelectScriptUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	int Index = 1;

	while(true)
	{
		FString BorderText = FString::Printf(TEXT("Border%d"), Index);
		FString TextBlockText = FString::Printf(TEXT("TextBlock%d"), Index);
		
		UTextBlock* TextBlockScript = Cast<UTextBlock>(GetWidgetFromName(FName(TextBlockText)));
		UBorder* BorderBackground = Cast<UBorder>(GetWidgetFromName(FName(BorderText)));

		if(false == IsValid(TextBlockScript)
			|| false == IsValid(BorderBackground))
		{
			break;
		}

		ScreenSelectScripts.Add(FScreenSelectScript(TextBlockScript, BorderBackground));

		++Index;
	}

	LimitProgressBar = Cast<UProgressBar>(GetWidgetFromName(FName("ProgressBarLimit")));
}

void UScreenSelectScriptUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UScreenSelectScriptUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UScreenSelectScriptUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(LimitTime > 0.f)
	{
		CurrentTime += InDeltaTime;

		if(IsValid(LimitProgressBar))
		{
			LimitProgressBar->SetPercent(CurrentTime / LimitTime);
		}
	}	
}

void UScreenSelectScriptUserWidget::SetText(float InLimitTime, const TArray<FString>& Texts)
{
	LimitTime = InLimitTime;
	
	UVerticalBoxSlot* ProgressBarVerticalBoxSlot = Cast<UVerticalBoxSlot>(LimitProgressBar);

	if(IsValid(ProgressBarVerticalBoxSlot))
	{
		FSlateChildSize SlateChildSize;
		SlateChildSize.SizeRule =ESlateSizeRule::Type::Fill;

		if(LimitTime <= 0.f)
		{
			SlateChildSize.Value = 0.f;			
		}
		else
		{
			SlateChildSize.Value = 1.f;
		}	
			
		ProgressBarVerticalBoxSlot->SetSize(SlateChildSize);		
	}

	int Index = Texts.Num();
	int MaxCount = ScreenSelectScripts.Num();
	int Count = ScreenSelectScripts.Num();

	if(Index < Count)
	{
		Count = Index;
	}

	SelectCount = Count;

	for(int i = 0; i < Count; ++i)
	{
		ScreenSelectScripts[i].TextBlock->SetText(FText::FromString(Texts[i]));
		ScreenSelectScripts[i].Border->SetBrushColor(FLinearColor(1.f, 1.f, 1.f, 0.f));
		UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(ScreenSelectScripts[i].Border->Slot);

		if(IsValid(VerticalBoxSlot))
		{
			FSlateChildSize SlateChildSize;
			SlateChildSize.SizeRule =ESlateSizeRule::Type::Fill;
			SlateChildSize.Value = 1.f;
			
			VerticalBoxSlot->SetSize(SlateChildSize);		
		}
	}

	for(int i = Count; Count < MaxCount; ++i)
	{
		ScreenSelectScripts[i].TextBlock->SetText(FText::FromString(""));
		ScreenSelectScripts[i].Border->SetBrushColor(FLinearColor(1.f, 1.f, 1.f, 0.f));
		UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(ScreenSelectScripts[i].Border->Slot);

		if(IsValid(VerticalBoxSlot))
		{
			FSlateChildSize SlateChildSize;
			SlateChildSize.SizeRule =ESlateSizeRule::Type::Fill;
			SlateChildSize.Value = 0.f;
			
			VerticalBoxSlot->SetSize(SlateChildSize);		
		}		
	}

	SetSelectIndex(0);
}

int32 UScreenSelectScriptUserWidget::GetSelectCount() const
{
	return SelectCount;
}

void UScreenSelectScriptUserWidget::SetSelectIndex(int Index)
{
	if(SelectIndex < SelectCount)
	{
		ScreenSelectScripts[SelectIndex].Border->SetBrushColor(FLinearColor(1.f, 1.f, 1.f, 0.f));	
	
		SelectIndex = Index;

		ScreenSelectScripts[SelectIndex].Border->SetBrushColor(FLinearColor(1.f, 1.f, 1.f, 1.f));		
	}
}