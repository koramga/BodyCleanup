// Fill out your copyright notice in the Description page of Project Settings.


#include "MainScreenWidget.h"
#include "../Script/ScreenScriptUserWidget.h"
#include "../Script/ScreenSelectScriptUserWidget.h"
#include "Components/CanvasPanelSlot.h"

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

		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(ScreenScriptUserWidget->Slot);

		if(IsValid(CanvasPanelSlot))
		{
			FVector2D Alignment = CanvasPanelSlot->GetAlignment();

			ScreenScriptPosition = CanvasPanelSlot->GetPosition();
			//만약에 사용자가 Top을 기준으로 정의했을 경우에는 Alignment가 티가 나니까 음수를 곱함으로써 탑에서 정의하더라도 정상적으로 동작할 수 있도록 한다.
			if(Alignment.Y == 0.f)
			{			
				ScreenScriptPosition.Y *= -1.f;
			}			
		}

		SetScreenScriptBottom(true);
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

void UMainScreenWidget::SetScreenScriptBottom(bool bIsBottom)
{
	if(IsValid(ScreenScriptUserWidget))
	{
		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(ScreenScriptUserWidget->Slot);

		if(IsValid(CanvasPanelSlot))
		{
			if(bIsBottom)
			{
				CanvasPanelSlot->SetPosition(FVector2D(0.f, ScreenScriptPosition.Y));
				CanvasPanelSlot->SetAlignment(FVector2D(0.5f, 1.f));
			}
			else
			{
				CanvasPanelSlot->SetPosition(FVector2D(0.f, -ScreenScriptPosition.Y));
				CanvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.f));				
			}
		}		
	}
}
