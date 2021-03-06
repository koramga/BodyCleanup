// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseUserWidget.h"
#include "BaseScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UBaseScreenWidget : public UBaseUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected :
	void SetFocusOnCharacter(bool bIsFocusOnCharacter);
	bool IsFocusOnCharacter() const;

public :
	virtual void InputUp();
	virtual void InputDown();
	virtual void InputEnter();
};
