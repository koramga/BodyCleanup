// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseElementWidget.h"
#include "KeyboardElementWidget.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UKeyboardElementWidget : public UBaseElementWidget
{
	GENERATED_BODY()

protected :
	UPROPERTY()
	class UTextBlock* TextHelp;

	UPROPERTY()
	class UImage* ImageHelp;

	bool bIsSetImage = false;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public :
	void SetText(const FString& Text) const;
	void SetImagePath(const FString& Path);
};
