// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseScriptUserWidget.h"
#include "Components/TextBlock.h"
#include "BubbleScriptUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UBubbleScriptUserWidget : public UBaseScriptUserWidget
{
	GENERATED_BODY()

protected :
	UPROPERTY()
	class UTextBlock*	TextBlockScript;

	UPROPERTY()
	class UBorder*		BorderBackground;

	UPROPERTY()
	class UImage*		ImageSpeaker;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public :
	virtual void SetText(const FString& String);
};
