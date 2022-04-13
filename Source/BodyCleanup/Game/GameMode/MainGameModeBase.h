// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameModeBase.h"
#include "Core/Dungeon.h"
#include "MainGameModeBase.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_OneParam(FOnLevelStart, UObject*);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ADungeon*			Dungeon;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool				bIsDungeonReady;
	bool				bIsNeedDungeonBuild;
	bool				bIsEndInitDungeon = false;
	
protected :
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void StartMatch() override;

protected:
	void BeginPlayForDungeonArchitecture();
	
	UFUNCTION()
	void OnInitialChunksLoaded(ADungeon* InDungeon);

	UFUNCTION(BlueprintCallable)
	bool IsReadyToStartMatch() const;
	
	void	BuildDungeon();

private:
	UFUNCTION()
	void __OnRobotCorpseActorDestroyed(AActor* Actor, EEndPlayReason::Type EndPlayReason);

public :
	TSoftObjectPtr<class UMainScreenWidget>	GetMainScreenWidget() const;
	TSoftObjectPtr<class UPauseMenuScreenWidget> GetPauseMenuScreenWidget() const;
	bool IsDungeonReady() const;

public:
	FOnLevelStart OnLevelStartDelegate;

public :
	void TogglePauseMenu();
	bool IsEnablePauseMenu();
	void SetEnablePauseMenu(bool bIsEnable);
	void SetRobotCorpse(const TArray<TSoftObjectPtr<class ARobotCorpseActor>>& InRobotCorpseActors);
};