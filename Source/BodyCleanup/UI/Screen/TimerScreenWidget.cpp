// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerScreenWidget.h"
#include "Components/TextBlock.h"

void UTimerScreenWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UTimerScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTimerScreenWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UTimerScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);

	if (!bStarted)
		return;

	if (RemainTime > 0)
	{
		RemainTime -= InDeltaTime;

		SetTimeText(RemainTime);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TimeOut!!"));
	}
}

void UTimerScreenWidget::SetTimeText(float Time)
{
	const FString TextTime = TimetoString(Time);

	Text_Time->SetText(FText::FromString(TextTime));
}

FString UTimerScreenWidget::TimetoString(float Time)
{
	const FTimespan TimeSpan = FTimespan::FromSeconds(Time);

	int32 Minutes = TimeSpan.GetMinutes();
	int32 Seconds = TimeSpan.GetSeconds();

	FString TimeString = "";

	if (Minutes < 10)
	{
		TimeString.Append("0");
	}

	TimeString.Append(FString::FromInt(Minutes));
	TimeString.Append(" : ");

	if (Seconds < 10)
	{
		TimeString.Append("0");
	}

	TimeString.Append(FString::FromInt(Seconds));

	return TimeString;
}

void UTimerScreenWidget::StartTimer()
{
	bStarted = true;
}