// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseScreenWidget.h"
#include "MainScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UMainScreenWidget : public UBaseScreenWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	class UScreenScriptUserWidget* ScreenScriptUserWidget;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public :
	void SetHiddenInGameScreenScript(bool bIsHiddenInGame);
	void SetScreenScriptText(const FString& Speaker, const FString& Text);
};
