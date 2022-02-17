// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameModeBase.h"
#include "MainGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API AMainGameModeBase : public ABaseGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMainScreenWidget*	MainScreenWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UPauseMenuScreenWidget>	PauseMenuScreenWidgetClass;

	class UPauseMenuScreenWidget*	PauseMenuScreenWidget;
	
protected :
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;

public :
	TSoftObjectPtr<class UMainScreenWidget>	GetMainScreenWidget() const;
	TSoftObjectPtr<class UPauseMenuScreenWidget> GetPauseMenuScreenWidget() const;

public :
	void TogglePauseMenu();
	bool IsEnablePauseMenu();
	void SetEnablePauseMenu(bool bIsEnable);
};
