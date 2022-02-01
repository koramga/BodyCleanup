// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseScriptUserWidget.h"
#include "ScreenSelectScriptUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UScreenSelectScriptUserWidget : public UBaseScriptUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
