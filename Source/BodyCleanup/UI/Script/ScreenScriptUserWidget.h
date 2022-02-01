// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseScriptUserWidget.h"
#include "ScreenScriptUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UScreenScriptUserWidget : public UBaseScriptUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	class UTextBlock*	TextBlockSpeaker;

	UPROPERTY()
	class UTextBlock*	TextBlockScript;

	UPROPERTY()
	class UBorder*		BorderBackground;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public :
	void SetText(const FString& Speaker, const FString& Text);
};
