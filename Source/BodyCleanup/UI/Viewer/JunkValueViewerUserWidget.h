// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseViewerUserWidget.h"
#include "JunkValueViewerUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UJunkValueViewerUserWidget : public UBaseViewerUserWidget
{
	GENERATED_BODY()

protected :
	UPROPERTY(VisibleAnywhere)
	class UBorder*	BorderJunkValue;
	
	UPROPERTY(VisibleAnywhere)
	class UTextBlock* TextBlockJunkValue;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public :
	void SetJunkValue(int32 InJunkValue);
};
