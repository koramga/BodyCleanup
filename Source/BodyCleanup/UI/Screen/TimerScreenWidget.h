// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseScreenWidget.h"
#include "TimerScreenWidget.generated.h"


UCLASS()
class BODYCLEANUP_API UTimerScreenWidget : public UBaseScreenWidget
{
public:

	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadWrite, Category = "Time")
		class UTextBlock* Text_Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		float RemainTime;  //남은시간

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Time")
		float ExtraTime; // 추가시간

	void SetTimeText(float Time);
	FString TimetoString(float Time);

public:
	void StartTimer();

private :
	bool bStarted = false;
};
