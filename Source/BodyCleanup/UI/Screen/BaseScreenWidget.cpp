// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseScreenWidget.h"
#include "../../Game/GameMode/BaseGameModeBase.h"

void UBaseScreenWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UBaseScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseScreenWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBaseScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBaseScreenWidget::SetFocusOnCharacter(bool bIsFocusOnCharacter)
{
	ABaseGameModeBase* BaseGameModeBase = Cast<ABaseGameModeBase>(GetWorld()->GetAuthGameMode());

	if(IsValid(BaseGameModeBase))
	{
		BaseGameModeBase->SetFocusOnCharacter(bIsFocusOnCharacter);
	}		
}

bool UBaseScreenWidget::IsFocusOnCharacter() const
{
	ABaseGameModeBase* BaseGameModeBase = Cast<ABaseGameModeBase>(GetWorld()->GetAuthGameMode());

	if(IsValid(BaseGameModeBase))
	{
		return BaseGameModeBase->IsFocusOnCharacter();
	}

	return true;
}

void UBaseScreenWidget::InputUp()
{
}

void UBaseScreenWidget::InputDown()
{
}

void UBaseScreenWidget::InputEnter()
{
}
