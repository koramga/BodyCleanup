// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseScreenWidget.h"
#include "MainScreenWidget.generated.h"

/**
 * 
 */

USTRUCT()
struct FKeyboardElementGroup
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<class UKeyboardElementWidget*>	KeyboardElementWidgets;
};

UCLASS()
class BODYCLEANUP_API UMainScreenWidget : public UBaseScreenWidget
{
	GENERATED_BODY()

protected:	
	UPROPERTY()
	class UScreenScriptUserWidget* ScreenScriptUserWidget;
	
	UPROPERTY()
	class UScreenSelectScriptUserWidget* ScreenSelectScriptUserWidget;

	UPROPERTY()
	FVector2D	ScreenScriptPosition;
	
	UPROPERTY()
	FVector2D	ScreenSelectScriptPosition;

	UPROPERTY()
	TMap<EKeyboardControlType, FKeyboardElementGroup>	KeyboardControlMap;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UKeyboardElementWidget>	KeyboardElementWidgetClass;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private :
	void __CallbackTimeOverSelectScreenScript();

public :
	virtual void InputUp() override;
	virtual void InputDown() override;
	virtual void InputEnter() override;
	
public :
	void SetHiddenInGameScreenScript(bool bIsHiddenInGame);
	void SetHiddenInGameScreenSelectScript(bool bIsHiddenInGame);
	void SetScreenScriptText(const FString& Speaker, const FString& Text);
	void SetScreenSelectScriptTexts(float InLimitTime, const TArray<FString>& Texts);
	void SetScreenScriptBottom(bool bIsBottom);
	void SetScreenSelectScriptBottom(bool bIsBottom);
};
