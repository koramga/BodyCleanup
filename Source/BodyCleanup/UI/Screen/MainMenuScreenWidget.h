// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseScreenWidget.h"
#include "MainMenuScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UMainMenuScreenWidget : public UBaseScreenWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	class UButton* ButtonGameStart;
	UPROPERTY()
	class UButton* ButtonGameExit;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName	GameStartLevelName;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private :
	UFUNCTION()
	void __OnGameStart();
	UFUNCTION()
	void __OnGameExit();
};
