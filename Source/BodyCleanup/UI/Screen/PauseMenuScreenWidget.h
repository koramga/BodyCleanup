// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseScreenWidget.h"
#include "PauseMenuScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UPauseMenuScreenWidget : public UBaseScreenWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	class UButton* ButtonGameContinue;
	UPROPERTY()
	class UButton* ButtonGameSetting;
	UPROPERTY()
	class UButton* ButtonBackToTitle;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private :
	UFUNCTION()
	void __OnClickedGameContinue();
	UFUNCTION()
	void __OnClickedGameSetting();
	UFUNCTION()
	void __OnClickedBackToTitle();
};
