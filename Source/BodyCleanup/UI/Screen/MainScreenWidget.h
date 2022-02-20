// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseScreenWidget.h"
#include "../../Data/TableRow/TableRows.h"
#include "Camera/CameraComponent.h"
#include "Layout/Margin.h"
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

USTRUCT()
struct FMainScreenWidgetScript
{
	GENERATED_BODY()

	UPROPERTY()
	TSoftObjectPtr<AActor>	Actor;
	
	UPROPERTY()
	FString					Script;

	UPROPERTY()
	TSoftObjectPtr<UCameraComponent> CameraComponent;
};

UCLASS()
class BODYCLEANUP_API UMainScreenWidget : public UBaseScreenWidget
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|MainScreenWidget")
	TSubclassOf<class UKeyboardElementWidget>	KeyboardElementWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|MainScreenWidget")
	FMargin KeyboardControlPadding;
	
protected:	
	UPROPERTY()
	class UScreenScriptUserWidget* ScreenScriptUserWidget;
	
	UPROPERTY()
	class UScreenSelectScriptUserWidget* ScreenSelectScriptUserWidget;

	UPROPERTY()
	class UCorpseElementWidget*	CorpseElementWidget;

	UPROPERTY()
	FVector2D	ScreenScriptPosition;
	
	UPROPERTY()
	FVector2D	ScreenSelectScriptPosition;

	UPROPERTY()
	TMap<EKeyboardControlType, FKeyboardElementGroup>	KeyboardControlMap;

	UPROPERTY()
	class UVerticalBox*	VerticalBoxKeyboardElement;

	EKeyboardControlType KeyboardControlType;

protected:
	UPROPERTY()
	TArray<FMainScreenWidgetScript> MainScreenWidgetScripts;

	int								MainScreenWidgetScriptIndex = -1;
	
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
	void SetScreenScriptScripts(const TArray<FMainScreenWidgetScript>& InScripts);
	void StartScript();
	void SetNextScript();
	void SetEndScript();
	bool IsEndScript() const;
	void SetScreenScriptBottom(bool bIsBottom);
	void SetScreenSelectScriptBottom(bool bIsBottom);
	void SetKeyboardControlType(EKeyboardControlType InKeyboardControlType);
	void AddCorpseCount();
	void SetMaxCorpseCount(int32 MaxCorpseCount);
	void ResetCorpseCount();
};
