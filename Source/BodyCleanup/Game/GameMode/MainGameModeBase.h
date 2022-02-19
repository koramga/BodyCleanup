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

	UPROPERTY()
	TArray<TSoftObjectPtr<class ARobotCorpseActor>> RobotCorpseActors;
	
protected :
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void __OnRobotCorpseActorDestroyed(AActor* Actor, EEndPlayReason::Type EndPlayReason);

public :
	TSoftObjectPtr<class UMainScreenWidget>	GetMainScreenWidget() const;
	TSoftObjectPtr<class UPauseMenuScreenWidget> GetPauseMenuScreenWidget() const;

public :
	void TogglePauseMenu();
	bool IsEnablePauseMenu();
	void SetEnablePauseMenu(bool bIsEnable);
	void SetRobotCorpse(const TArray<TSoftObjectPtr<class ARobotCorpseActor>>& InRobotCorpseActors);
};
