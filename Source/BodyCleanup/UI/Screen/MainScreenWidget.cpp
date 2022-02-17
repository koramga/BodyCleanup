// Fill out your copyright notice in the Description page of Project Settings.


#include "MainScreenWidget.h"
#include "../Script/ScreenScriptUserWidget.h"
#include "../Script/ScreenSelectScriptUserWidget.h"
#include "../../Game/GameInstance/BaseGameInstance.h"
#include "../../Game/GameMode/MainGameModeBase.h"
#include "../../Data/TableRow/TableRows.h"
#include "../Element/KeyboardElementWidget.h"
#include "Components/CanvasPanelSlot.h"

void UMainScreenWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	ScreenScriptUserWidget = Cast<UScreenScriptUserWidget>(GetWidgetFromName(TEXT("UI_ScreenScript")));
	ScreenSelectScriptUserWidget = Cast<UScreenSelectScriptUserWidget>(GetWidgetFromName(TEXT("UI_ScreenSelectScript")));
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

	if(IsValid(ScreenSelectScriptUserWidget))
	{
		ScreenSelectScriptUserWidget->SetHiddenInGame(true);

		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(ScreenSelectScriptUserWidget->Slot);

		if(IsValid(CanvasPanelSlot))
		{
			FVector2D Alignment = CanvasPanelSlot->GetAlignment();

			ScreenSelectScriptPosition = CanvasPanelSlot->GetPosition();
			//만약에 사용자가 Top을 기준으로 정의했을 경우에는 Alignment가 티가 나니까 음수를 곱함으로써 탑에서 정의하더라도 정상적으로 동작할 수 있도록 한다.
			if(Alignment.Y == 0.f)
			{			
				ScreenSelectScriptPosition.Y *= -1.f;
			}			
		}

		SetScreenSelectScriptBottom(true);
		ScreenSelectScriptUserWidget->SetCallbackSelectScreenScriptTimeOver(this, &UMainScreenWidget::__CallbackTimeOverSelectScreenScript);
	}

	if(IsValid(KeyboardElementWidgetClass))
	{
		UBaseGameInstance* BaseGameInstance = Cast<UBaseGameInstance>(GetWorld()->GetAuthGameMode()->GetGameInstance());

		if(IsValid(BaseGameInstance))
		{
			TArray<FKeyboardControlTableRow> KeyboardControlTableRows;
		
			BaseGameInstance->GetKeyboardControlElements(KeyboardControlTableRows);

			for(const FKeyboardControlTableRow& KeyboardControlTableRow : KeyboardControlTableRows)
			{
				UKeyboardElementWidget* KeyboardElementWidget = Cast<UKeyboardElementWidget>(CreateWidget(this, KeyboardElementWidgetClass));

				if(IsValid(KeyboardElementWidget))
				{
					FKeyboardElementGroup* KeyboardElementGroup = KeyboardControlMap.Find(KeyboardControlTableRow.Type);

					if(nullptr == KeyboardElementGroup)
					{
						KeyboardControlMap.Add(KeyboardControlTableRow.Type);

						KeyboardElementGroup = KeyboardControlMap.Find(KeyboardControlTableRow.Type);
					}

					if(nullptr != KeyboardElementGroup)
					{
						KeyboardElementGroup->KeyboardElementWidgets.Add(KeyboardElementWidget);
					}
				}
			}
		}		
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

void UMainScreenWidget::__CallbackTimeOverSelectScreenScript()
{
	if(false == ScreenSelectScriptUserWidget->IsHiddenInGame())
	{
		SetHiddenInGameScreenSelectScript(true);
	}
}

void UMainScreenWidget::InputUp()
{
	Super::InputUp();

	if(false == ScreenSelectScriptUserWidget->IsHiddenInGame())
	{
		ScreenSelectScriptUserWidget->UpSelect();
	}
}

void UMainScreenWidget::InputDown()
{
	Super::InputDown();

	if(false == ScreenSelectScriptUserWidget->IsHiddenInGame())
	{
		ScreenSelectScriptUserWidget->DownSelect();
	}
}

void UMainScreenWidget::InputEnter()
{
	Super::InputEnter();

	if(false == IsFocusOnCharacter())
	{
		if(false == ScreenSelectScriptUserWidget->IsHiddenInGame())
		{
			SetHiddenInGameScreenSelectScript(true);
		}
		else if(false == ScreenScriptUserWidget->IsHiddenInGame())
		{
			SetHiddenInGameScreenScript(true);
		}
	}
	
}

void UMainScreenWidget::SetHiddenInGameScreenScript(bool bIsHiddenInGame)
{
	if(IsValid(ScreenScriptUserWidget))
	{
		ScreenScriptUserWidget->SetHiddenInGame(bIsHiddenInGame);
		SetFocusOnCharacter(bIsHiddenInGame);
	}
}

void UMainScreenWidget::SetHiddenInGameScreenSelectScript(bool bIsHiddenInGame)
{
	if(IsValid(ScreenSelectScriptUserWidget))
	{
		ScreenSelectScriptUserWidget->SetHiddenInGame(bIsHiddenInGame);
		SetFocusOnCharacter(bIsHiddenInGame);
	}
}

void UMainScreenWidget::SetScreenScriptText(const FString& Speaker, const FString& Text)
{
	if(IsValid(ScreenScriptUserWidget))
	{
		ScreenScriptUserWidget->SetText(Speaker, Text);
	}	
}

void UMainScreenWidget::SetScreenSelectScriptTexts(float InLimitTime, const TArray<FString>& Texts)
{
	if(IsValid(ScreenScriptUserWidget))
	{
		ScreenSelectScriptUserWidget->SetText(InLimitTime, Texts);
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

void UMainScreenWidget::SetScreenSelectScriptBottom(bool bIsBottom)
{
	if(IsValid(ScreenSelectScriptUserWidget))
	{
		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(ScreenSelectScriptUserWidget->Slot);

		if(IsValid(CanvasPanelSlot))
		{
			if(bIsBottom)
			{
				CanvasPanelSlot->SetPosition(FVector2D(0.f, ScreenSelectScriptPosition.Y));
				CanvasPanelSlot->SetAlignment(FVector2D(0.5f, 1.f));
			}
			else
			{
				CanvasPanelSlot->SetPosition(FVector2D(0.f, -ScreenSelectScriptPosition.Y));
				CanvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.f));				
			}
		}		
	}
}
