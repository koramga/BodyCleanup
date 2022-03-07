// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "ScriptEditorUtilityWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, meta = (ShowWorldContextPin), config = Editor)
class SCRIPTDESINGERTOOLS_API UScriptEditorUtilityWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

protected :
	class UButton* ButtonWriteJson;
	class UButton* ButtonReadJson;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

private:
	UFUNCTION()
	void __OnButtonClickedWriteJson();
	UFUNCTION()
	void __OnButtonClickedReadJson();
	
};
